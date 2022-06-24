zephyr_sources(heci.c)
zephyr_sources_ifdef(CONFIG_SMHI            smhi_client.c)
