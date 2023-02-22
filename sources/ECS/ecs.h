// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>

#include "mpl.h"

#include "ecs_defs.h"

// You should define a file ../game/ecs_defs.h with the list of your
// components, groups, and handlers. See ecs_defs_example.h for an
// example file
//
//#if __has_include("ecs_defs.h")
//#include "ecs_defs.h"
//#else
//#define _CMPS_LIST_ _CMP_1
//#define _GRPS_LIST_ _GRP_2
//#define _HDLRS_LIST_ _HDLR_1
//#endif

#ifndef  _CMPS_LIST_
class ___DummyComponent____;
#define _CMPS_LIST_ ___DummyComponent____
#endif

#ifndef  _GRPS_LIST_
struct ___DummyGroup____;
#define _GRPS_LIST_ ___DummyGroup____
#endif

#ifndef  _HDLRS_LIST_
struct ___DummyHandler____;
#define _HDLRS_LIST_ ___DummyHandler____
#endif


class Entity;
class Component;

namespace ecs {

	using ComponentsList = mpl::TypeList<_CMPS_LIST_>;
	using GroupsList = mpl::TypeList<_GRPS_LIST_>;
	using HdlrsList = mpl::TypeList<_HDLRS_LIST_>;

	template<typename T>
	constexpr std::size_t cmpIdx = mpl::IndexOf<T, ComponentsList>();

	template<typename T>
	constexpr std::size_t grpIdx = mpl::IndexOf<T, GroupsList>();

	template<typename T>
	constexpr std::size_t hdlrIdx = mpl::IndexOf<T, HdlrsList>();


	constexpr std::size_t maxComponent = ComponentsList::size;
	constexpr std::size_t maxGroup = GroupsList::size;
	constexpr std::size_t maxHdlr = HdlrsList::size;
}

//namespace ecs {
// 
//
//	class EntityManager;
//	class Entity;
//	class Component;
//
//	// We define type for the identifiers so we can change them easily.
//	// For example, if we have less than 256 components we can use one
//	// byte, i.e. uint8_t, if we have up to 512 we can use uint16_t,
//	// and so on ...
//	//
//	using cmpId_type = uint8_t;
//	using grpId_type = uint8_t;
//	using hdlrId_type = uint8_t;
//
//
//
//	// list of component identifiers
//	enum cmpId : cmpId_type {
//		_CMPS_LIST_, /* taken from ecs_defs */
//
//		// do not remove this
//		_LAST_CMP_ID
//	};
//
//	// list of group identifiers
//	enum grpId : cmpId_type {
//		_grp_GENERAL,
//		_GRPS_LIST_, /* taken from ecs_defs */
//
//		// do not remove this
//		_LAST_GRP_ID
//	};
//
//	// list of handler identifiers
//	enum hdlrId : hdlrId_type {
//		_HDLRS_LIST_, /* taken from ecs_defs */
//
//		// do not remove this
//		_LAST_HDLR_ID
//	};
//
//	constexpr cmpId_type maxComponentId = cmpId::_LAST_CMP_ID;
//	constexpr cmpId_type maxGroupId = grpId::_LAST_GRP_ID;
//	constexpr hdlrId_type maxHandlerId = hdlrId::_LAST_HDLR_ID;
//
//	// a macro for component identifier declaration, e.g., __CMPID_DECL__(ecs::_TRANSFORM)
//	// expands to:
//	//
//	//   constexpr static ecs::cmpId_type id = ecs::_TRANSFORM;
//	//
//#define __CMPID_DECL__(cId) constexpr static ecs::cmpId_type id = cId;
//
//} // end of namespace

