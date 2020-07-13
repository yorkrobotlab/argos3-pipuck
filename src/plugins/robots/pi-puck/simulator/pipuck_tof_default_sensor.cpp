/**
 * @file <argos3/plugins/robots/pi-puck/simulator/pipuck_tof_default_sensor.cpp>
 *
 * @author C Wringe - <uint8.lotte@gmail.com>
 */

#include "pipuck_tof_default_sensor.h"

#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/physics_engine/physics_model.h>

#define SHORT_RANGE 1.360
#define MED_RANGE 2.900
#define LONG_RANGE 3.600



namespace argos {

   CPiPuckTofDefaultSensor::CPiPuckTofDefaultSensor() :
   m_bShowRays(false), /* false by default, I think, because otherwise the rays show even when the sensor isn't called? TODO: check this is true*/
   m_rRange(SHORT_RANGE),
   m_pcControllableEntity(nullptr) {}

   void CPiPuckTofDefaultSensor::SetRobot(CComposableEntity& c_entity) {
      m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));

      m_vecSimulatedInterfaces.reserve(m_mapSensorConfig.size());

      for(const std::pair<const UInt8, TConfiguration>& t_config : m_mapSensorConfig) {
         const char* pchAnchor = std::get<const char*>(t_config.second);
         SAnchor& sAnchor =
            c_entity.GetComponent<CEmbodiedEntity>("body").GetAnchor(pchAnchor);
         m_vecSimulatedInterfaces.emplace_back(t_config.first, sAnchor);
       }
   }

   void CPiPuckTofDefaultSensor::Init(TConfigurationNode& t_tree) {
      try {
         CCI_PiPuckTofSensor::Init(t_tree);
         GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
         GetNodeAttributeOrDefault(t_tree, "range", m_rRange, m_rRange);

         for(SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
            s_interface.Range = m_rRange;
         }
      }
      catch(CARGoSException& ex){
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in the Pi-Puck ToF sensor.", ex);
      }
   }

   void CPiPuckTofDefaultSensor::Update() {
      /* buffers */
      CRay3 cSensorRay;
      CVector3 cRayStart, cRayEnd; 
      SEmbodiedEntityIntersectionItem sIntersection;

      /* go through the sensors (same as rangefinders, as the config is defined in the controller) */
      for(SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
         cRayStart = std::get<CVector3>(s_interface.Configuration);
         cRayStart.Rotate(s_interface.Anchor.Orientation); /*no rotation at the start of the ray, given it's the origin*/
         cRayStart += s_interface.Anchor.Position;
         cRayEnd = CVector3::Z * s_interface.Range; /*this is the range - given the ToF sensor has three possible ones, I'm going to have to find a good way to figure that out*/
         cRayEnd.Rotate(std::get<CQuaternion>(s_interface.Configuration)); /*orientation according to the start of the ray*/
         cRayEnd += cRayStart; /* end position = start position + range */
         cSensorRay.Set(cRayStart, cRayEnd); /*Ray defined by start and end points*/

         if(GetClosestEmbodiedEntityIntersectedByRay(sIntersection, cSensorRay)) {
            /* there is an intersection */
            /* should be the same as rayfinder - after all, both are IR proximity sensors */
            if(m_bShowRays) {
               m_pcControllableEntity->AddIntersectionPoint(cSensorRay, sIntersection.TOnRay);
               m_pcControllableEntity->AddCheckedRay(true, cSensorRay); /*change the colour of the ray*/
            }
            s_interface.Reading = 
               ConvertToMeters(cSensorRay.GetDistance(sIntersection.TOnRay));
         } else {
            /*No intersection */
            if(m_bShowRays) {
               s_interface.Reading = s_interface.Range; /* If there is no intersection, the reading is how far the sensor can see */
               if(m_bShowRays) {
                  m_pcControllableEntity->AddCheckedRay(false, cSensorRay);
               }
            }
         }
      }
   }

   void CPiPuckTofDefaultSensor::Reset() {
      for(SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
         s_interface.Reading = s_interface.Reading; /*when resetting, the default is the range of the sensor*/
      }
   }

   void CPiPuckTofDefaultSensor::ForEachInterface(std::function<void(const SInterface&)> fn) {
      for(const SSimulatedInterface& s_interface : m_vecSimulatedInterfaces) {
         fn(s_interface);
      }
   }

   REGISTER_SENSOR(CPiPuckTofDefaultSensor,
                  "pipuck_tof", "default", 
                  "C Wringe [uint8.lotte@gmail.com]",
                  "1.0",
                  "Time-of-flight long-range IR sensors for the pi-puck",
                  "This sensor measures the distance of far away objects\n"
                  "ranges:\n" 
                  "SHORT_RANGE - 1.360m"
                  "MED_RANGE - 2.900m\n"
                  "LONG_RANGE - 3.600m\n",
                  "Under development"
   );



}