/**
 * @file <argos3/plugins/robots/pi-puck/simulator/pipuck_entity.cpp>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#include "pipuck_entity.h"

#include <argos3/core/simulator/simulator.h>
#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/utility/datatypes/color.h>

#include <argos3/plugins/simulator/entities/debug_entity.h>
#include <argos3/plugins/simulator/entities/directional_led_equipped_entity.h>
#include <argos3/plugins/simulator/entities/radio_equipped_entity.h>
#include <argos3/plugins/simulator/entities/tag_equipped_entity.h>
#include <argos3/plugins/simulator/media/directional_led_medium.h>
#include <argos3/plugins/simulator/media/radio_medium.h>
#include <argos3/plugins/simulator/media/tag_medium.h>

#include <argos3/plugins/robots/pi-puck/simulator/pipuck_differential_drive_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   const CVector3 CPiPuckEntity::TAG_OFFSET_POSITION = {0.0, 0.0, 0.1385};

   const CVector3 CPiPuckEntity::WIFI_OFFSET_POSITION = {0.0, 0.0, 0.05};

   const Real     CPiPuckEntity::TAG_SIDE_LENGTH = 0.0235;

   const Real     CPiPuckEntity::WIFI_TRANSMISSION_RANGE = 10.0;

   /****************************************/
   /****************************************/

   CPiPuckEntity::CPiPuckEntity(const std::string& str_id,
                                const std::string& str_controller_id,
                                const CVector3& c_position,
                                const CQuaternion& c_orientation,
                                bool b_debug,
                                const std::string& str_wifi_medium,
                                const std::string& str_tag_medium,
                                const std::string& str_led_medium) :
      CComposableEntity(nullptr, str_id),
      m_pcControllableEntity(nullptr),
      m_pcDebugEntity(nullptr),
      m_pcEmbodiedEntity(nullptr),
      m_pcDifferentialDriveEntity(nullptr),
      m_bDebug(b_debug) {
      /* create and initialize the embodied entity */
      m_pcEmbodiedEntity = new CEmbodiedEntity(this, "body_0", c_position, c_orientation);
      AddComponent(*m_pcEmbodiedEntity);
      SAnchor& sOriginAnchor = m_pcEmbodiedEntity->GetOriginAnchor();
      /* create additional anchors */
      m_pcEmbodiedEntity->AddAnchor("body", {0.0, 0.0, 0.00125});
      m_pcEmbodiedEntity->AddAnchor("left_wheel");
      m_pcEmbodiedEntity->AddAnchor("right_wheel");
      /* create and initialize the differential drive entity */
      m_pcDifferentialDriveEntity
         = new CPiPuckDifferentialDriveEntity(this, "differential_drive_0");
      AddComponent(*m_pcDifferentialDriveEntity);
      m_pcDifferentialDriveEntity->Enable();
      /* create and initialize the tags */
      m_pcTagEquippedEntity = new CTagEquippedEntity(this, "tags_0");
      m_pcTagEquippedEntity->AddTag("tag_0",
                                    TAG_OFFSET_POSITION,
                                    CQuaternion(),
                                    m_pcEmbodiedEntity->GetOriginAnchor(),
                                    CRadians::PI_OVER_THREE,
                                    TAG_SIDE_LENGTH,
                                    GetId());
      if(!str_tag_medium.empty()) {
         CTagMedium& cTagMedium =
            CSimulator::GetInstance().GetMedium<CTagMedium>(str_tag_medium);
         m_pcTagEquippedEntity->SetMedium(cTagMedium);
         m_pcTagEquippedEntity->Enable();
      }
      AddComponent(*m_pcTagEquippedEntity);
      /* create and initialize a radio equipped entity for WiFi */
      m_pcWifiRadioEquippedEntity = new CRadioEquippedEntity(this, "radios_0");
      m_pcWifiRadioEquippedEntity->AddRadio("wifi",
         WIFI_OFFSET_POSITION,
         m_pcEmbodiedEntity->GetOriginAnchor(),
         WIFI_TRANSMISSION_RANGE);
      if(!str_wifi_medium.empty()) {
         CRadioMedium& cWifiRadioMedium =
            CSimulator::GetInstance().GetMedium<CRadioMedium>(str_wifi_medium);
         m_pcWifiRadioEquippedEntity->SetMedium(cWifiRadioMedium);
         m_pcWifiRadioEquippedEntity->Enable();
      }
      AddComponent(*m_pcWifiRadioEquippedEntity);     
      /* create and initialize the directional LED equipped entity */
      m_pcDirectionalLEDEquippedEntity = new CDirectionalLEDEquippedEntity(this, "leds_0");
      m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_0",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(),
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_1",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(), 
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_2",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(),
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_3",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(),
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_4",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(),
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_5",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(), 
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_6",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(),
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_7",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(),
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      m_pcDirectionalLEDEquippedEntity->AddLED("front_led",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(),
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      m_pcDirectionalLEDEquippedEntity->AddLED("body_led",
                                               CVector3(0, 0, 0.025),
                                               CQuaternion(),
                                               sOriginAnchor,
                                               CRadians::PI_OVER_THREE,
                                               CColor::BLACK);
      if(!str_led_medium.empty()) {
         CDirectionalLEDMedium& cDirectionalLEDMedium = 
            CSimulator::GetInstance().GetMedium<CDirectionalLEDMedium>(str_led_medium);
         m_pcDirectionalLEDEquippedEntity->SetMedium(cDirectionalLEDMedium);
         m_pcDirectionalLEDEquippedEntity->Enable();
      }
      AddComponent(*m_pcDirectionalLEDEquippedEntity);
      /* create and initialize a debugging entity */
      m_pcDebugEntity = new CDebugEntity(this, "debug_0");
      AddComponent(*m_pcDebugEntity);
      /* Create and initialize the controllable entity */
      m_pcControllableEntity = new CControllableEntity(this, "controller_0");
      AddComponent(*m_pcControllableEntity);
      m_pcControllableEntity->SetController(str_controller_id);
      /* Update components */
      UpdateComponents();
   }

   /****************************************/
   /****************************************/

   void CPiPuckEntity::Init(TConfigurationNode& t_tree) {
      try {
         /* initialize the base class */
         CComposableEntity::Init(t_tree);
         /* check if we are debugging */
         GetNodeAttributeOrDefault(t_tree, "debug", m_bDebug, m_bDebug);
         /* create and initialize the embodied entity */
         m_pcEmbodiedEntity = new CEmbodiedEntity(this);
         AddComponent(*m_pcEmbodiedEntity);
         m_pcEmbodiedEntity->Init(GetNode(t_tree, "body"));
         SAnchor& sOriginAnchor = m_pcEmbodiedEntity->GetOriginAnchor();
         /* create additional anchors */
         m_pcEmbodiedEntity->AddAnchor("body", {0.0, 0.0, 0.00125});
         m_pcEmbodiedEntity->AddAnchor("left_wheel");
         m_pcEmbodiedEntity->AddAnchor("right_wheel");
         /* create and initialize the differential drive entity */
         m_pcDifferentialDriveEntity
            = new CPiPuckDifferentialDriveEntity(this, "differential_drive_0");
         AddComponent(*m_pcDifferentialDriveEntity);
         m_pcDifferentialDriveEntity->Enable();
         /* create and initialize the tags */
         m_pcTagEquippedEntity = new CTagEquippedEntity(this, "tags_0");
         m_pcTagEquippedEntity->AddTag("tag_0",
                                       TAG_OFFSET_POSITION,
                                       CQuaternion(),
                                       m_pcEmbodiedEntity->GetOriginAnchor(),
                                       CRadians::PI_OVER_THREE,
                                       TAG_SIDE_LENGTH,
                                       GetId());
         std::string strTagMedium;
         GetNodeAttributeOrDefault(t_tree, "tag_medium", strTagMedium, strTagMedium);
         if(!strTagMedium.empty()) {
            CTagMedium& cTagMedium =
               CSimulator::GetInstance().GetMedium<CTagMedium>(strTagMedium);
            m_pcTagEquippedEntity->SetMedium(cTagMedium);
            m_pcTagEquippedEntity->Enable();
         }
         AddComponent(*m_pcTagEquippedEntity);
         /* create and initialize a radio equipped entity for the wifi */
         m_pcWifiRadioEquippedEntity = new CRadioEquippedEntity(this, "radios_0");
         m_pcWifiRadioEquippedEntity->AddRadio("wifi",
            WIFI_OFFSET_POSITION,
            m_pcEmbodiedEntity->GetOriginAnchor(),
            WIFI_TRANSMISSION_RANGE);
         std::string strWifiMedium;
         GetNodeAttributeOrDefault(t_tree, "wifi_medium", strWifiMedium, strWifiMedium);
         if(!strWifiMedium.empty()) {
            CRadioMedium& cWifiRadioMedium =
               CSimulator::GetInstance().GetMedium<CRadioMedium>(strWifiMedium);
            m_pcWifiRadioEquippedEntity->SetMedium(cWifiRadioMedium);
            m_pcWifiRadioEquippedEntity->Enable();
         }
         AddComponent(*m_pcWifiRadioEquippedEntity);
         /* create and initialize the directional LED equipped entity */
         m_pcDirectionalLEDEquippedEntity = new CDirectionalLEDEquippedEntity(this, "leds_0");
         m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_0",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(),
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_1",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(), 
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_2",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(),
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_3",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(),
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_4",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(),
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_5",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(), 
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_6",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(),
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         m_pcDirectionalLEDEquippedEntity->AddLED("ring_led_7",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(),
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         m_pcDirectionalLEDEquippedEntity->AddLED("front_led",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(),
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         m_pcDirectionalLEDEquippedEntity->AddLED("body_led",
                                                  CVector3(0, 0, 0.025),
                                                  CQuaternion(),
                                                  sOriginAnchor,
                                                  CRadians::PI_OVER_THREE,
                                                  CColor::BLACK);
         std::string strLedMedium;
         GetNodeAttributeOrDefault(t_tree, "led_medium", strLedMedium, strLedMedium);
         if(!strLedMedium.empty()) {
            CDirectionalLEDMedium& cDirectionalLedMedium =
               CSimulator::GetInstance().GetMedium<CDirectionalLEDMedium>(strLedMedium);
            m_pcDirectionalLEDEquippedEntity->SetMedium(cDirectionalLedMedium);
            m_pcDirectionalLEDEquippedEntity->Enable();
         }
         AddComponent(*m_pcDirectionalLEDEquippedEntity);
         /* create and initialize a debugging entity */
         m_pcDebugEntity = new CDebugEntity(this, "debug_0");
         AddComponent(*m_pcDebugEntity);
         /* Create and initialize the controllable entity */
         m_pcControllableEntity = new CControllableEntity(this);
         AddComponent(*m_pcControllableEntity);
         m_pcControllableEntity->Init(GetNode(t_tree, "controller"));
         /* Update components */
         UpdateComponents();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize PiPuck", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CPiPuckEntity::UpdateComponents() {
      /* update all components using base class method */
      CComposableEntity::UpdateComponents();
   }

   /****************************************/
   /****************************************/

   REGISTER_ENTITY(CPiPuckEntity,
                   "pipuck",
                   "1.0",
                   "Michael Allwright [allsey87@gmail.com]",
                   "The Pi-Puck robot",
                   "Long description",
                   "Usable"
   );

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_SPACE_OPERATIONS_ON_COMPOSABLE(CPiPuckEntity);

   /****************************************/
   /****************************************/

}
