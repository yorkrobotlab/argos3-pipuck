/**
 * @file <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_tof_sensor.h>
 *
 * @author C Wringe <uint8.lotte@gmail.com>
 */

#ifndef CCI_PIPUCK_TOF_SENSOR_H
#define CCI_PIPUCK_TOF_SENSOR_H

namespace argos {
    class CCI_PiPuckTofSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>

#include <map>
#include <tuple>
#include <functional>

namespace argos {
   
   class CCI_PiPuckTofSensor : public CCI_Sensor {
   

   public:
      

      using TConfiguration = std::tuple<const char*, CVector3, CQuaternion>;

      struct SInterface {
          SInterface(const UInt8& un_label) :
             Label(un_label),
             Configuration(m_mapSensorConfig.at(un_label)),
             Reading(0.0f) {}
         const UInt8& Label;
         const TConfiguration& Configuration;
         Real Range;
         Real Reading;
         bool Enabled;
      };

      virtual ~CCI_PiPuckTofSensor() {}

      virtual void ForEachInterface(std::function<void(const SInterface&)>) = 0;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);

#endif
   protected:

      static const std::map<UInt8, TConfiguration> m_mapSensorConfig;

   };
}

#endif