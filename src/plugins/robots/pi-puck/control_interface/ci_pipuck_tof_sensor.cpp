/**
 * @file <argos3/plugins/robots/pi-puck/control_interface/ci_pipuck_tof_sensor.cpp>
 *
 * @author C Wringe <uint8.lotte@gmail.com>
 */

#include "ci_pipuck_tof_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_PiPuckTofSensor::CreateLuaState(lua_State* pt_lua_state) {
      CLuaUtility::StartTable(pt_lua_state, "tof");
      ForEachInterface([pt_lua_state] (const SInterface& s_interface) {
         CLuaUtility::StartTable(pt_lua_state, s_interface.Label);
         CLuaUtility::AddToTable(pt_lua_state, "reading", s_interface.Reading);
         CLuaUtility::StartTable(pt_lua_state, "transform");
         CLuaUtility::AddToTable(pt_lua_state, "position", std::get<CVector3>(s_interface.Configuration));
         CLuaUtility::AddToTable(pt_lua_state, "orientation", std::get<CQuaternion>(s_interface.Configuration));
         CLuaUtility::AddToTable(pt_lua_state, "anchor", std::get<const char*>(s_interface.Configuration));
         CLuaUtility::EndTable(pt_lua_state);
         CLuaUtility::EndTable(pt_lua_state);
      });
      CLuaUtility::EndTable(pt_lua_state);
   }
#endif

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_PiPuckTofSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
      lua_getfield(pt_lua_state, -1, "tof");
      ForEachInterface([pt_lua_state] (const SInterface& s_interface) {
         lua_pushnumber(pt_lua_state, s_interface.Label);
         lua_gettable(pt_lua_state, -2);
         lua_pushstring(pt_lua_state, "reading");
         lua_pushnumber(pt_lua_state, s_interface.Reading);
         lua_settable(pt_lua_state, -3);
         lua_pop(pt_lua_state, 1);
      });
      lua_pop(pt_lua_state, 1);
   }
#endif

   /****************************************/
   /****************************************/

   /* taken from JA's specification */
   /* height is a complete and utter guess, and mostly just there to make sure I have _something_. TODO: check & fix this*/

    const std::map<UInt8, CCI_PiPuckTofSensor::TConfiguration > CCI_PiPuckTofSensor::m_mapSensorConfig = {
            std::make_pair(1,  std::make_tuple("origin", CVector3( 0.0309, 0.0, 0.05), CQuaternion(0.5 * CRadians::PI, CVector3(0.0, 1.0, 0)))),
            std::make_pair(2,  std::make_tuple("origin", CVector3( 0.02075, -0.02285, 0.05), CQuaternion(0.5 * CRadians::PI, CVector3(0.70711, 0.70711, 0)))),
            std::make_pair(3,  std::make_tuple("origin", CVector3( -0.0209, -0.02265, 0.05), CQuaternion(0.5 * CRadians::PI, CVector3(0.70711, -0.70711, 0)))),
            std::make_pair(4,  std::make_tuple("origin", CVector3( -0.02785, -0.0001, 0.05), CQuaternion(0.5 * CRadians::PI, CVector3(0, -1.0, 0)))), // Offset from the y-axis by 0.1mm in the hardware
            std::make_pair(5,  std::make_tuple("origin", CVector3( -0.0209, 0.02265, 0.05), CQuaternion(0.5 * CRadians::PI, CVector3(-0.70711, -0.70711, 0)))),
            std::make_pair(6,  std::make_tuple("origin", CVector3( 0.0206, 0.023, 0.05), CQuaternion(0.5 * CRadians::PI, CVector3(-0.70711, 0.70711, 0)))),
    };

   /****************************************/
   /****************************************/
}
