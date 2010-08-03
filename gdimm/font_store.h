#pragma once

#include "font_man.h"
#include "helper_def.h"

using namespace std;

class gdimm_font_store
{
	// face name -> font id
	// we use this map because FreeType callback only have face id
	map<wstring, long> _reg_name_to_id;
	map<wstring, long> _linked_name_to_id;
	// font id -> font info
	// we use this map because vector internally free and re-allocate existing entries
	// pointers become invalid
	map<long, font_info> _id_to_info;

	typedef map<long, const gdimm_font_man *> font_man_tls_map;
	DWORD _tls_index;
	list<font_man_tls_map *> _all_font_man_tls;

	static DWORD get_font_size(HDC font_holder, DWORD &table_header);
	static ULONG get_ttc_face_index(HDC font_holder, DWORD ttc_file_size);

	font_man_tls_map *create_font_man_tls();

public:
	gdimm_font_store();
	~gdimm_font_store();

	font_info *lookup_font(long font_id);
	long register_font(HDC font_holder, const wchar_t *font_face);
	long link_font(HDC font_holder, HFONT linked_hfont, wstring &linked_font_face);
	void register_font_man(long font_id, const gdimm_font_man *font_man);
	const gdimm_font_man *lookup_font_man(long font_id);
};