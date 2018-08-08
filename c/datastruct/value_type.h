//
// Created by hujianzhe
//

#ifndef UTIL_C_DATASTRUCT_VALUE_TYPE_H
#define	UTIL_C_DATASTRUCT_VALUE_TYPE_H

typedef struct value_t {
	void(*deleter)(void*);
	union {
		long long valueint;
		float valuefloat;
		double valuedouble;
		void* valueobject;
		const char* valuestring_const;
		char* valuestring;
		struct {
			unsigned char* begin;
			unsigned char* end;
		} valueblob;
	};
#ifdef __cplusplus
	value_t(void) : deleter((void(*)(void*))0) {}
	~value_t(void) {
		if (deleter) {
			deleter(valueobject);
			deleter = (void(*)(void*))0;
		}
	}
#endif
} value_t;

static void value_deleter(struct value_t* v) {
	if (v->deleter) {
		v->deleter(v->valueobject);
		v->deleter = (void(*)(void*))0;
	}
}

#endif // !UTIL_C_DATASTRUCT_VALUE_TYPE_H