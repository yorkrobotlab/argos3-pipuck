#include "test_pipuck_cpp.h"
#include <argos3/core/utility/configuration/argos_configuration.h>

CTestPipuckCpp::CTestPipuckCpp() :
   m_pcLEDs(NULL),
   m_pcDrive(NULL),
   m_pcGround(NULL)
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
   std::vector<Real> vecReadings;
   Real Readings[3];
   size_t i = 0;
   m_pcGround->ForEachInterface([&vecReadings, &Readings, &i] (const CCI_PiPuckGroundSensor::SInterface& s_interface)
   {
      vecReadings.emplace_back(s_interface.Reading);
      std::cout << "Label: " << s_interface.Label << std::endl;
      std::cout << "Reading: " << s_interface.Reading << std::endl;
      Readings[i%3] = s_interface.Reading;
      i ++;

      const CCI_PiPuckGroundSensor::TConfiguration configuration = s_interface.Configuration;
      std::cout << "Name: " << std::get<0>(configuration) << std::endl;
      std::cout << "Position: " << std::get<1>(configuration) << std::endl;
      std::cout << "Orientation: " << std::get<2>(configuration) << std::endl;
      std::cout << "Range: " << std::get<3>(configuration) << std::endl;

      std::cout << std::endl;

   }
   );
   if(Readings[2] < 0.6) {
      if(Readings[0] < 0.6) {
         m_pcDrive->SetTargetVelocityLeft(0.01);
         m_pcDrive->SetTargetVelocityRight(-0.00); 
         std::cout << "right"  << std::endl;
      } else {
         m_pcDrive->SetTargetVelocityLeft(0.01);
         m_pcDrive->SetTargetVelocityRight(0.01); 
         std::cout << "hard right" << std::endl;
      }
   } else if(Readings[1] < 0.6) {
      if(Readings[0] < 0.6) {
         m_pcDrive->SetTargetVelocityLeft(0.00);
         m_pcDrive->SetTargetVelocityRight(-0.01);  
         std::cout << "left" << std::endl; 
      } else {
         m_pcDrive->SetTargetVelocityLeft(-0.01);
         m_pcDrive->SetTargetVelocityRight(-0.01);  
         std::cout << "hard left" << std::endl; 
      }
   } else {
      m_pcDrive->SetTargetVelocityLeft(0.005);
      m_pcDrive->SetTargetVelocityRight(-0.005);
      std::cout << "straight ahead" <<std::endl;
   }

   if(count < 10) {
      count ++;
      m_pcLEDs->SetSingleColor(count, CColor::RED);
   } else {
      count = 1;
      m_pcLEDs->SetAllColors(CColor::BLACK);
   }


}

REGISTER_CONTROLLER(CTestPipuckCpp, "test_ccp_controller")
