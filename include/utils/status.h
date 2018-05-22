// .h
#define G_ERROR_MAP(X_ENTRY) \
	X_ENTRY(EARGINVAL, "invalid arguments") \
	X_ENTRY(ESDL2, "sdl2 specific failure")

typedef enum {
	#define ERROR_MAP_EXPAND_AS_ENUM(type, _) \
		type,

	G_ERROR_MAP(ERROR_MAP_EXPAND_AS_ENUM)

	#undef ERROR_MAP_EXPAND_AS_ENUM	
} G_ERROR_TYPE;

void set_error(ERROR_TYPE type);
const char* get_error(void);



// .c
// need to make thread safe
static struct {
	ERROR_TYPE current_error_type;		
} __ERROR;

#define ERROR_MAP_EXPAND_AS_CASE(type, _) \
	case type: return #type; 	
static const char* error_get_type_str(G_ERROR_TYPE type)
{
	switch (type) {
		G_ERROR_MAP(ERROR_MAP_EXPAND_AS_CASE)		
	default:
		return "unknown error type";
	}
}
#undef ERROR_MAP_EXPAND_AS_CASE

#define ERROR_MAP_EXPAND_AS_CASE(type, msg) \
	case type: return msg; 	
static const char* error_get_msg_str(G_ERROR_TYPE type)
{
	switch (type) {
		G_ERROR_MAP(ERROR_MAP_EXPAND_AS_CASE)		
	default:
		return "unknown error string";
	}
}
#undef ERROR_MAP_EXPAND_AS_CASE

#define ANSI_COLOUR_CLEAR "\x1b[0m"
#define ANSI_COLOUR_RED "\x1b[31m"
const char* get_error_msg(void)
{
	char buf[256];

	strcat(buf, "ANSI_COLOUR_CLEAR");
	strcat(buf, "ANSI_COLOUR_RED");
	strcat(buf, error_get_type_str(__ERROR.current_error_type));
	strcat(buf, error_get_msg_str(__ERROR.current_error_type));
	strcat(buf, "ANSI_COLOUR_CLEAR");

	return "";
}

void set_error(ERROR_TYPE error_type)
{
	__ERROR.current_error_type = error_type;		
}

