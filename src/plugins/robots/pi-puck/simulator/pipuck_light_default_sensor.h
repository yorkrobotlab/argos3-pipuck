/**
 * @file <argos3/plugins/robots/foot-bot/simulator/footbot_light_rotzonly_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef PIPUCK_LIGHT_DEFAULT_SENSOR_H
#define PIPUCK_LIGHT_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CPiPuckLightDefaultSensor;
   class CLightSensorEquippedEntity;
}

#include <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_light_sensor.h>
#include <argos3/core/utility/math/range.h>
#include <argos3/core/utility/math/rng.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/sensor.h>

namespace argos {

   class CPiPuckLightDefaultSensor : public CSimulatedSensor,
                                      public CCI_PiPuckLightSensor {

   public:

      CPiPuckLightDefaultSensor();

      virtual ~CPiPuckLightDefaultSensor() {}

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

     void Enable();

     void Disable();

   protected:

      /** Is this sensor currently enabled? */
      bool             m_bEnabled;
      /** Reference to embodied entity associated to this sensor */
      CEmbodiedEntity* m_pcEmbodiedEntity;

      /** Reference to light sensor equipped entity associated to this sensor */
      CLightSensorEquippedEntity* m_pcLightEntity;

      /** Reference to controllable entity associated to this sensor */
      CControllableEntity* m_pcControllableEntity;

      /** Flag to show rays in the simulator */
      bool m_bShowRays;

      /** Random number generator */
      CRandom::CRNG* m_pcRNG;

      /** Whether to add noise or not */
      bool m_bAddNoise;

      /** Noise range */
      CRange<Real> m_cNoiseRange;

      /** Reference to the space */
      CSpace& m_cSpace;
   };

}

#endif