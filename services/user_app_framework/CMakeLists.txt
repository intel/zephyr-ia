zephyr_include_directories(include)
zephyr_sources_ifdef(CONFIG_IA_USER_APP_FRAMEWORK non_user_mode_framework.c)
