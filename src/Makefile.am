bin_PROGRAMS=sngrep
sngrep_SOURCES=capture.c capture_ws.c sip.c sip_call.c sip_msg.c sip_attr.c main.c option.c
sngrep_SOURCES+=group.c filter.c keybinding.c media.c setting.c rtp.c util.c vector.c
sngrep_SOURCES+=ui_manager.c ui_call_list.c ui_call_flow.c ui_call_raw.c
sngrep_SOURCES+=ui_filter.c ui_save.c ui_msg_diff.c ui_column_select.c ui_settings.c

if WITH_OPENSSL
sngrep_SOURCES+=capture_tls.c 
endif
