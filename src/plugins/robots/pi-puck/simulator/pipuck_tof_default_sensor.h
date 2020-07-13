/**
 * @file <argos3/plugins/robots/pi-puck/simulator/pipuck_tof_default_sensor.h>
 *
 * @author C Wringe - <uint8.lotte@gmail.com>
 */

#ifndef PIPUCK_TOF_DEFAULT_SENSOR_H
#define PIPUCK_TOF_DEFAULT_SENSOR_H

namespace argos {
   class CPiPuckTofDefaultSensor;
   class CControllableEntity;
   class CEmbodiedEntity;
   struct SAnchor;
    
}

#include <argos3/core/simulator/sensor.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>
#include <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_tof_sensor.h>

namespace argos {
   class CPiPuckTofDefaultSensor : public CSimulatedSensor,
                                   public CCI_PiPuckTofSensor {

   public:
      
      struct SSimulatedInterface : SInterface 
      {
          /* constructor */
         SSimulatedInterface(const UInt8& un_label,
                             const SAnchor& s_anchor) :
            SInterface(un_label),
            Anchor(s_anchor) {}
         /* members */
         const SAnchor& Anchor;
      };

      CPiPuckTofDefaultSensor();

      virtual ~CPiPuckTofDefaultSensor() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

      virtual void ForEachInterface(std::function<void(const SInterface&)> fn);

   private: 
      Real ConvertToMeters(Real f_raw) {
         static const Real fConversionFactor = Real(1.0);
         return (f_raw * fConversionFactor);
      }

      Real ConvertToLux(Real f_raw) {
         static const Real fConversionFactor = Real(1.0);
         return (f_raw * fConversionFactor);
      }
   
   private:
      bool m_bShowRays;
      Real m_rRange;
      std::string m_sRange;
      CControllableEntity* m_pcControllableEntity;
      std::vector<SSimulatedInterface> m_vecSimulatedInterfaces;   
   };
   
}

#endif