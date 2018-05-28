#ifndef __game_handlers_event_handlers_h__
#define __game_handlers_event_handlers_h__

#define G_EVENT_HANDLERS_MAP(X_ENTRY) \
	X_ENTRY(G_VIEW_GAME, g_events) \
	X_ENTRY(G_VIEW_MENU, g_menu_manager_events) \

#define G_EVENT_HANDLERS_EXPAND_AS_CASE(view_id, handler) \
	case view_id: handler;

#endif
