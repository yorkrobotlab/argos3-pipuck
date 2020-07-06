/**
 * @file <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_ground_sensor.h>
 *
 * @author Michael Allwright <allsey87@gmail.com>
 */

#ifndef CCI_PIPUCK_GROUND_SENSOR_H
#define CCI_PIPUCK_GROUND_SENSOR_H

namespace argos {
   class CCI_PiPuckGroundSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/vector3.h>
#include <argos3/core/utility/math/quaternion.h>

#include <map>
#include <tuple>
#include <functional>

namespace argos {

   class CCI_PiPuckGroundSensor : public CCI_Sensor {

   public:

      using TConfiguration = std::tuple<std::string, CVector3, CQuaternion, Real>;

      struct SInterface {
         /* constructor */
         SInterface(const std::string& str_label) :
            Label(str_label),
            Configuration(m_mapSensorConfig.at(str_label)),
            Reading(0.0) {}
         /* members */
         const std::string& Label;
         const TConfiguration& Configuration;
         Real Reading;
      };

      struct SReadings {
         /**
          * Left reagind
          */
         Real Left;

         /**
          * Center reading
          */
         Real Center;

         /**
          * Right reading
          */
         Real Right;

         /**
          * Empty constructor
          */
         SReadings() :
            Left(0.0f),
            Center(0.0f),
            Right(0.0f) {}

         /**
          * Reset the reading (ie. all 0)
          */
         void Reset() {
            Left = 0.0f;
            Center = 0.0f;
            Right = 0.0f;
         }
         
                  /**
          * Define a new operator [] to allow accessing to readings like an array
          *
          * @param un_idx id of the field to acces. 0 -> Left, 1 -> Center and 2 -> Right
          */
         Real& operator[] (size_t un_idx) {
            if(un_idx == 0) return Left;
            else if(un_idx == 1) return Center;
            else if(un_idx == 2) return Right;
            else THROW_ARGOSEXCEPTION("Index of out bound accessing the ground sensor reading. "
                                      << "Expected [0-2], got: " << un_idx);
         }

        Real const& operator[] (size_t un_idx) const {
            if(un_idx == 0) return Left;
            else if(un_idx == 1) return Center;
            else if(un_idx == 2) return Right;
            else THROW_ARGOSEXCEPTION("Index of out bound accessing the ground sensor reading. "
                                      << "Expected [0-2], got: " << un_idx);
         }
      };

      /**
       * Returns the sensor data as a SReadings.
       * @return the sensor data as a SReadings
       */
      inline const SReadings& GetReadings() const {
         return m_sReadings;
      }

      /**
       * Returns the sensor data as an array of 3 elements.
       * @return the sensor data as an array of 3 elements.
       */
      inline void GetReadings(Real* pf_buffer) const {
         pf_buffer[0] = m_sReadings.Left;
         pf_buffer[1] = m_sReadings.Center;
         pf_buffer[2] = m_sReadings.Right;
      }

      inline Real GetReading(size_t un_idx) {
         return m_sReadings[un_idx];
      }

      virtual ~CCI_PiPuckGroundSensor() {}

      virtual void ForEachInterface(std::function<void(const SInterface&)>) = 0;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

   protected:

      static const std::map<std::string, TConfiguration> m_mapSensorConfig;

      SReadings m_sReadings;

   }; 

}

#endif
