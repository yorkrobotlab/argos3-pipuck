#ifndef TEST_PIPUCK_CPP_H
#define TEST_PIPUCK_CPP_H

#include <argos3/core/control_interface/ci_controller.h>
#include <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_differential_drive_actuator.h>
/* Definition of the LEDs actuator */
#include <argos3/plugins/robots/generic/control_interface/ci_directional_leds_actuator.h>
#include <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_ground_sensor.h>

using namespace argos;

class CTestPipuckCpp : public CCI_Controller {

public:
   CTestPipuckCpp();

   virtual ~CTestPipuckCpp() {}

   virtual void Init(TConfigurationNode& t_node);

   virtual void ControlStep();

   virtual void Reset();

   virtual void Destroy() {}

   //some random count variable
private:
   CCI_DirectionalLEDsActuator* m_pcLEDs;
   CCI_PiPuckDifferentialDriveActuator* m_pcDrive;
   CCI_PiPuckGroundSensor* m_pcGround;
   UInt32 count;
};
#endif