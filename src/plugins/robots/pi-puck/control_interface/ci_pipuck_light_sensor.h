#ifndef CCI_PIPUCK_LIGHT_SENSOR_H
#define CCI_PIPUCK_LIGHT_SENSOR_H

namespace argos {
   class CCI_PiPuckLightSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/angles.h>
#include <vector>

namespace argos {

   class CCI_PiPuckLightSensor : public CCI_Sensor {

   public:

      /**
       * The DTO of the light sensor. It contains the reading of each sensor and
       * and the angle at which each sensor is placed.
       */
      struct SReading {
         Real Value;
         CRadians Angle;

         SReading() :
            Value(0.0f) {}

         SReading(Real f_value,
                  const CRadians& c_angle) :
            Value(f_value),
            Angle(c_angle) {}
      };

      typedef std::vector<SReading> TReadings;

   public:

      CCI_PiPuckLightSensor();
      virtual ~CCI_PiPuckLightSensor() {}

      /**
       * Returns the readings of this sensor
       */
      const TReadings& GetReadings() const;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

     virtual void Enable() = 0;

     virtual void Disable() = 0;

   protected:

      TReadings m_tReadings;
   };

   std::ostream& operator<<(std::ostream& c_os, const CCI_PiPuckLightSensor::SReading& s_reading);
   std::ostream& operator<<(std::ostream& c_os, const CCI_PiPuckLightSensor::TReadings& t_readings);

}

#endif
