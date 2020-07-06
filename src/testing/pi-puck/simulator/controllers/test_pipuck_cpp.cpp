#include "test_pipuck_cpp.h"
#include <argos3/core/utility/configuration/argos_configuration.h>

CTestPipuckCpp::CTestPipuckCpp() :
   m_pcLEDs(NULL)
   {}

void CTestPipuckCpp::Init(TConfigurationNode& t_node) {
   m_pcLEDs      = GetActuator<CCI_DirectionalLEDsActuator                >("directional_leds"                 );
   m_pcDrive     = GetActuator<CCI_PiPuckDifferentialDriveActuator        >("pipuck_differential_drive"        );
   m_pcGround    = GetSensor  <CCI_PiPuckGroundSensor                     >("pipuck_ground"                    );

   // Parse the configuration file
   //I need to get the other sensors/nodes probably

   Reset();
}

void CTestPipuckCpp::Reset() {
   count = 1;
}

void CTestPipuckCpp::ControlStep() {
   Real breadings[3];
   m_pcGround->GetReadings(breadings);

   if(count < 10) {
      count ++;
      m_pcLEDs->SetSingleColor(count, CColor::RED);
   } else {
      count = 1;
      m_pcLEDs->SetAllColors(CColor::BLACK);
   }
   if(breadings[2] < 0.6) {
      if(breadings[1] < 0.6) {
         m_pcDrive->SetTargetVelocityLeft(0.01);
         m_pcDrive->SetTargetVelocityRight(0.00);   
      } else {
         m_pcDrive->SetTargetVelocityLeft(0.01);
         m_pcDrive->SetTargetVelocityRight(-0.01); 
      }
   } else if(breadings[0] < 0.6) {
      if(breadings[1] < 0.6) {
         m_pcDrive->SetTargetVelocityLeft(0.00);
         m_pcDrive->SetTargetVelocityRight(0.01);   
      } else {
         m_pcDrive->SetTargetVelocityLeft(-0.01);
         m_pcDrive->SetTargetVelocityRight(0.01);   
      }
   }
   


}

REGISTER_CONTROLLER(CTestPipuckCpp, "test_ccp_controller")
