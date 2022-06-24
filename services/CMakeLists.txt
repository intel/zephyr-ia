#Placeholder for adding other services like eclite, oob, etc.

if (CONFIG_SYS_IA_SERVICE)
set(INTEL_SERV_DIR $ENV{ZEPHYR_BASE} /../ service / )
	zephyr_include_directories(
		${INTEL_SERV_DIR} / ia_services / host_services / include / )
	zephyr_include_directories(sys_service / include)
	add_subdirectory(user_app_framework)
	add_subdirectory(sys_services)
endif()
#add_subdirectory(fw_version)
