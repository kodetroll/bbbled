/*************************************************************************
 * color_defs.h - RGB Color definitions header file. Contains RGB Color tables 
 * in several forms. For each name in color_names, there is an associated
 * entry in the color_rgbs[] & color_tuples[] arrays of strings, and the 
 * unsigned char numeric color RGB arrays, hex (red_hex[], grn_hex[], 
 * blu_hex[]) and decimal (red[], grn[], blu[]).
 *
 * (C) 2015 KB4OID Labs, A division of Kodetroll Heavy Industries
 * Author: Kodetroll
 * Date: January 2015
 *
 *************************************************************************/

#ifndef __COLOR_DEFS_H__
#define __COLOR_DEFS_H__

#ifdef  __cplusplus
extern "C" {
#endif

// This is the number of colors in the list
#define NUM_COLORS 144

/* This is an enumerated list of color names that forms the index for all the other color tables
 * here. This list is to make it easy to call a color index by the name of its color.
 * 
 */
enum Color_Names {
	CLR_MAROON,CLR_DARK_RED,CLR_BROWN,CLR_FIREBRICK,CLR_CRIMSON,CLR_RED,CLR_TOMATO,CLR_CORAL,
	CLR_INDIAN_RED,CLR_LIGHT_CORAL,CLR_DARK_SALMON,CLR_SALMON,CLR_LIGHT_SALMON,CLR_ORANGE_RED,
	CLR_DARK_ORANGE,CLR_ORANGE,CLR_GOLD,CLR_DARK_GOLDEN_ROD,CLR_GOLDEN_ROD,CLR_PALE_GOLDEN_ROD,
	CLR_DARK_KHAKI,CLR_KHAKI,CLR_OLIVE,CLR_YELLOW,CLR_YELLOW_GREEN,CLR_DARK_OLIVE_GREEN,CLR_OLIVE_DRAB,
	CLR_LAWN_GREEN,CLR_CHART_REUSE,CLR_GREEN_YELLOW,CLR_DARK_GREEN,CLR_GREEN,CLR_FOREST_GREEN,
	CLR_LIME,CLR_LIME_GREEN,CLR_LIGHT_GREEN,CLR_PALE_GREEN,CLR_DARK_SEA_GREEN,CLR_MEDIUM_SPRING_GREEN,
	CLR_SPRING_GREEN,CLR_SEA_GREEN,CLR_MEDIUM_AQUA_MARINE,CLR_MEDIUM_SEA_GREEN,CLR_LIGHT_SEA_GREEN,
	CLR_DARK_SLATE_GRAY,CLR_TEAL,CLR_DARK_CYAN,CLR_AQUA,CLR_CYAN,CLR_LIGHT_CYAN,CLR_DARK_TURQUOISE,
	CLR_TURQUOISE,CLR_MEDIUM_TURQUOISE,CLR_PALE_TURQUOISE,CLR_AQUA_MARINE,CLR_POWDER_BLUE,CLR_CADET_BLUE,
	CLR_STEEL_BLUE,CLR_CORN_FLOWER_BLUE,CLR_DEEP_SKY_BLUE,CLR_DODGER_BLUE,CLR_LIGHT_BLUE,CLR_SKY_BLUE,
	CLR_LIGHT_SKY_BLUE,CLR_MIDNIGHT_BLUE,CLR_NAVY,CLR_DARK_BLUE,CLR_MEDIUM_BLUE,CLR_BLUE,CLR_ROYAL_BLUE,
	CLR_BLUE_VIOLET,CLR_INDIGO,CLR_DARK_SLATE_BLUE,CLR_SLATE_BLUE,CLR_MEDIUM_SLATE_BLUE,CLR_MEDIUM_PURPLE,
	CLR_DARK_MAGENTA,CLR_DARK_VIOLET,CLR_DARK_ORCHID,CLR_MEDIUM_ORCHID,CLR_PURPLE,CLR_THISTLE,CLR_PLUM,
	CLR_VIOLET,CLR_MAGENTA,CLR_FUCHSIA,CLR_ORCHID,CLR_MEDIUM_VIOLET_RED,CLR_PALE_VIOLET_RED,CLR_DEEP_PINK,
	CLR_HOT_PINK,CLR_LIGHT_PINK,CLR_PINK,CLR_ANTIQUE_WHITE,CLR_BEIGE,CLR_BISQUE,CLR_BLANCHED_ALMOND,CLR_WHEAT,
	CLR_CORN_SILK,CLR_LEMON_CHIFFON,CLR_LIGHT_GOLDEN_ROD_YELLOW,CLR_LIGHT_YELLOW,CLR_SADDLE_BROWN,CLR_SIENNA,
	CLR_CHOCOLATE,CLR_PERU,CLR_SANDY_BROWN,CLR_BURLY_WOOD,CLR_TAN,CLR_ROSY_BROWN,CLR_MOCCASIN,CLR_NAVAJO_WHITE,
	CLR_PEACH_PUFF,CLR_MISTY_ROSE,CLR_LAVENDER_BLUSH,CLR_LINEN,CLR_OLD_LACE,CLR_PAPAYA_WHIP,CLR_SEA_SHELL,
	CLR_MINT_CREAM,CLR_SLATE_GRAY,CLR_LIGHT_SLATE_GRAY,CLR_LIGHT_STEEL_BLUE,CLR_LAVENDER,CLR_FLORAL_WHITE,
	CLR_ALICE_BLUE,CLR_GHOST_WHITE,CLR_HONEYDEW,CLR_IVORY,CLR_AZURE,CLR_SNOW,CLR_BLACK,CLR_DIM_GRAY,CLR_DIM_GREY,
	CLR_GRAY,CLR_GREY,CLR_DARK_GRAY,CLR_DARK_GREY,CLR_SILVER,CLR_LIGHT_GRAY,CLR_LIGHT_GREY,CLR_GAINSBORO,
	CLR_WHITE_SMOKE,CLR_WHITE};

/* This is a string array list of colornames (144 in all), there are some duplications of RGB due 
 * to slightly different spellings of names (grey vs gray). For each entry here, there is an 
 * associated entry in the other lists.
 * 
 */
char color_names[144][26] = {
"maroon","dark red","brown","firebrick","crimson","red","tomato","coral","indian red","light coral",
"dark salmon","salmon","light salmon","orange red","dark orange","orange","gold","dark golden rod",
"golden rod","pale golden rod","dark khaki","khaki","olive","yellow","yellow green","dark olive green",
"olive drab","lawn green","chartreuse","green yellow","dark green","green","forest green","lime",
"lime green","light green","pale green","dark sea green","medium spring green","spring green",
"sea green","medium aqua marine","medium sea green","light sea green","dark slate gray","teal",
"dark cyan","aqua","cyan","light cyan","dark turquoise","turquoise","medium turquoise","pale turquoise",
"aqua marine","powder blue","cadet blue","steel blue","corn flower blue","deep sky blue","dodger blue",
"light blue","sky blue","light sky blue","midnight blue","navy","dark blue","medium blue","blue",
"royal blue","blue violet","indigo","dark slate blue","slate blue","medium slate blue","medium purple",
"dark magenta","dark violet","dark orchid","medium orchid","purple","thistle","plum","violet","magenta",
"fuchsia","orchid","medium violet red","pale violet red","deep pink","hot pink","light pink","pink",
"antique white","beige","bisque","blanched almond","wheat","corn silk","lemon chiffon","light golden rod yellow",
"light yellow","saddle brown","sienna","chocolate","peru","sandy brown","burly wood","tan","rosy brown",
"moccasin","navajo white","peach puff","misty rose","lavender blush","linen","old lace","papaya whip",
"sea shell","mint cream","slate gray","light slate gray","light steel blue","lavender","floral white",
"alice blue","ghost white","honeydew","ivory","azure","snow","black","dim gray","dim grey","gray",
"grey","dark gray","dark grey","silver","light gray","light grey","gainsboro","white smoke","white"
};

/* This is a string array list of color RGB hex values as used on the web. There is an entry 
 * in the list for each color name in color_names[]. These are strings and include the '#' RGB 
 * color prefix. Values are in HEX - '#RRGGBB'
 * 
 */
char color_rgbs[144][10] = {
	"#800000", "#8B0000", "#A52A2A", "#B22222", "#DC143C", "#FF0000", "#FF6347", "#FF7F50",
	"#CD5C5C", "#F08080", "#E9967A", "#FA8072", "#FFA07A", "#FF4500", "#FF8C00", "#FFA500",
	"#FFD700", "#B8860B", "#DAA520", "#EEE8AA", "#BDB76B", "#F0E68C", "#808000", "#FFFF00",
	"#9ACD32", "#556B2F", "#6B8E23", "#7CFC00", "#7FFF00", "#ADFF2F", "#006400", "#008000",
	"#228B22", "#00FF00", "#32CD32", "#90EE90", "#98FB98", "#8FBC8F", "#00FA9A", "#00FF7F",
	"#2E8B57", "#66CDAA", "#3CB371", "#20B2AA", "#2F4F4F", "#008080", "#008B8B", "#00FFFF",
	"#00FFFF", "#E0FFFF", "#00CED1", "#40E0D0", "#48D1CC", "#AFEEEE", "#7FFFD4", "#B0E0E6",
	"#5F9EA0", "#4682B4", "#6495ED", "#00BFFF", "#1E90FF", "#ADD8E6", "#87CEEB", "#87CEFA",
	"#191970", "#000080", "#00008B", "#0000CD", "#0000FF", "#4169E1", "#8A2BE2", "#4B0082",
	"#483D8B", "#6A5ACD", "#7B68EE", "#9370DB", "#8B008B", "#9400D3", "#9932CC", "#BA55D3",
	"#800080", "#D8BFD8", "#DDA0DD", "#EE82EE", "#FF00FF", "#FF00FF", "#DA70D6", "#C71585",
	"#DB7093", "#FF1493", "#FF69B4", "#FFB6C1", "#FFC0CB", "#FAEBD7", "#F5F5DC", "#FFE4C4",
	"#FFEBCD", "#F5DEB3", "#FFF8DC", "#FFFACD", "#FAFAD2", "#FFFFE0", "#8B4513", "#A0522D",
	"#D2691E", "#CD853F", "#F4A460", "#DEB887", "#D2B48C", "#BC8F8F", "#FFE4B5", "#FFDEAD",
	"#FFDAB9", "#FFE4E1", "#FFF0F5", "#FAF0E6", "#FDF5E6", "#FFEFD5", "#FFF5EE", "#F5FFFA",
	"#708090", "#778899", "#B0C4DE", "#E6E6FA", "#FFFAF0", "#F0F8FF", "#F8F8FF", "#F0FFF0",
	"#FFFFF0", "#F0FFFF", "#FFFAFA", "#000000", "#696969", "#696969", "#808080", "#808080",
	"#A9A9A9", "#A9A9A9", "#C0C0C0", "#D3D3D3", "#D3D3D3", "#DCDCDC", "#F5F5F5", "#FFFFFF"
};

/* This is a string array list of color RGB decimal values as tuples. There is an entry 
 * in the list for each color name in color_names[]. These are strings and are formatted
 * as '(R,G,B)', where R, G & B may range from 0 to 255 (8 bit color).
 * 
 */
char color_tuples[144][16] = {
"(128,0,0)","(139,0,0)","(165,42,42)","(178,34,34)","(220,20,60)","(255,0,0)","(255,99,71)","(255,127,80)",
"(205,92,92)","(240,128,128)","(233,150,122)","(250,128,114)","(255,160,122)","(255,69,0)","(255,140,0)","(255,165,0)",
"(255,215,0)","(184,134,11)","(218,165,32)","(238,232,170)","(189,183,107)","(240,230,140)","(128,128,0)","(255,255,0)",
"(154,205,50)","(85,107,47)","(107,142,35)","(124,252,0)","(127,255,0)","(173,255,47)","(0,100,0)","(0,128,0)",
"(34,139,34)","(0,255,0)","(50,205,50)","(144,238,144)","(152,251,152)","(143,188,143)","(0,250,154)","(0,255,127)",
"(46,139,87)","(102,205,170)","(60,179,113)","(32,178,170)","(47,79,79)","(0,128,128)","(0,139,139)","(0,255,255)",
"(0,255,255)","(224,255,255)","(0,206,209)","(64,224,208)","(72,209,204)","(175,238,238)","(127,255,212)","(176,224,230)",
"(95,158,160)","(70,130,180)","(100,149,237)","(0,191,255)","(30,144,255)","(173,216,230)","(135,206,235)","(135,206,250)",
"(25,25,112)","(0,0,128)","(0,0,139)","(0,0,205)","(0,0,255)","(65,105,225)","(138,43,226)","(75,0,130)",
"(72,61,139)","(106,90,205)","(123,104,238)","(147,112,219)","(139,0,139)","(148,0,211)","(153,50,204)","(186,85,211)",
"(128,0,128)","(216,191,216)","(221,160,221)","(238,130,238)","(255,0,255)","(255,0,255)","(218,112,214)","(199,21,133)",
"(219,112,147)","(255,20,147)","(255,105,180)","(255,182,193)","(255,192,203)","(250,235,215)","(245,245,220)","(255,228,196)",
"(255,235,205)","(245,222,179)","(255,248,220)","(255,250,205)","(250,250,210)","(255,255,224)","(139,69,19)","(160,82,45)",
"(210,105,30)","(205,133,63)","(244,164,96)","(222,184,135)","(210,180,140)","(188,143,143)","(255,228,181)","(255,222,173)",
"(255,218,185)","(255,228,225)","(255,240,245)","(250,240,230)","(253,245,230)","(255,239,213)","(255,245,238)","(245,255,250)",
"(112,128,144)","(119,136,153)","(176,196,222)","(230,230,250)","(255,250,240)","(240,248,255)","(248,248,255)","(240,255,240)",
"(255,255,240)","(240,255,255)","(255,250,250)","(0,0,0)","(105,105,105)","(105,105,105)","(128,128,128)","(128,128,128)",
"(169,169,169)","(169,169,169)","(192,192,192)","(211,211,211)","(211,211,211)","(220,220,220)","(245,245,245)","(255,255,255)"
};

/* This is a list of hexidecimal values representing only the Red portion of the RGB color for each index entry. 
 * There is an entry here for each element of color_names[]. Values are expressed as unsigned char in hex.
 * To use these tables, 'RGB_red = red_hex[CLR_COLOR_NAME]'
 */
unsigned char red_hex[] = {
	0x80, 0x8B, 0xA5, 0xB2, 0xDC, 0xFF, 0xFF, 0xFF,
	0xCD, 0xF0, 0xE9, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xB8, 0xDA, 0xEE, 0xBD, 0xF0, 0x80, 0xFF,
	0x9A, 0x55, 0x6B, 0x7C, 0x7F, 0xAD, 0x00, 0x00,
	0x22, 0x00, 0x32, 0x90, 0x98, 0x8F, 0x00, 0x00,
	0x2E, 0x66, 0x3C, 0x20, 0x2F, 0x00, 0x00, 0x00,
	0x00, 0xE0, 0x00, 0x40, 0x48, 0xAF, 0x7F, 0xB0,
	0x5F, 0x46, 0x64, 0x00, 0x1E, 0xAD, 0x87, 0x87,
	0x19, 0x00, 0x00, 0x00, 0x00, 0x41, 0x8A, 0x4B,
	0x48, 0x6A, 0x7B, 0x93, 0x8B, 0x94, 0x99, 0xBA,
	0x80, 0xD8, 0xDD, 0xEE, 0xFF, 0xFF, 0xDA, 0xC7,
	0xDB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0xF5, 0xFF,
	0xFF, 0xF5, 0xFF, 0xFF, 0xFA, 0xFF, 0x8B, 0xA0,
	0xD2, 0xCD, 0xF4, 0xDE, 0xD2, 0xBC, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFA, 0xFD, 0xFF, 0xFF, 0xF5,
	0x70, 0x77, 0xB0, 0xE6, 0xFF, 0xF0, 0xF8, 0xF0,
	0xFF, 0xF0, 0xFF, 0x00, 0x69, 0x69, 0x80, 0x80,
	0xA9, 0xA9, 0xC0, 0xD3, 0xD3, 0xDC, 0xF5, 0xFF
};

/* This is a list of hexidecimal values representing only the Green portion of the RGB color for each index 
 * entry. There is an entry here for each element of color_names[]. Values are expressed as unsigned char in hex.
 * To use these tables, 'RGB_grn = grn_hex[CLR_COLOR_NAME]' 
 */
unsigned char grn_hex[] = {
	0x00, 0x00, 0x2A, 0x22, 0x14, 0x00, 0x63, 0x7F,
	0x5C, 0x80, 0x96, 0x80, 0xA0, 0x45, 0x8C, 0xA5,
	0xD7, 0x86, 0xA5, 0xE8, 0xB7, 0xE6, 0x80, 0xFF,
	0xCD, 0x6B, 0x8E, 0xFC, 0xFF, 0xFF, 0x64, 0x80,
	0x8B, 0xFF, 0xCD, 0xEE, 0xFB, 0xBC, 0xFA, 0xFF,
	0x8B, 0xCD, 0xB3, 0xB2, 0x4F, 0x80, 0x8B, 0xFF,
	0xFF, 0xFF, 0xCE, 0xE0, 0xD1, 0xEE, 0xFF, 0xE0,
	0x9E, 0x82, 0x95, 0xBF, 0x90, 0xD8, 0xCE, 0xCE,
	0x19, 0x00, 0x00, 0x00, 0x00, 0x69, 0x2B, 0x00,
	0x3D, 0x5A, 0x68, 0x70, 0x00, 0x00, 0x32, 0x55,
	0x00, 0xBF, 0xA0, 0x82, 0x00, 0x00, 0x70, 0x15,
	0x70, 0x14, 0x69, 0xB6, 0xC0, 0xEB, 0xF5, 0xE4,
	0xEB, 0xDE, 0xF8, 0xFA, 0xFA, 0xFF, 0x45, 0x52,
	0x69, 0x85, 0xA4, 0xB8, 0xB4, 0x8F, 0xE4, 0xDE,
	0xDA, 0xE4, 0xF0, 0xF0, 0xF5, 0xEF, 0xF5, 0xFF,
	0x80, 0x88, 0xC4, 0xE6, 0xFA, 0xF8, 0xF8, 0xFF,
	0xFF, 0xFF, 0xFA, 0x00, 0x69, 0x69, 0x80, 0x80,
	0xA9, 0xA9, 0xC0, 0xD3, 0xD3, 0xDC, 0xF5, 0xFF
};

/* This is a list of hexidecimal values representing only the Blue portion of the RGB color for each index 
 * entry. There is an entry here for each element of color_names[]. Values are expressed as unsigned char in hex.
 * To use these tables, 'RGB_blu = blu_hex[CLR_COLOR_NAME]' 
 */
unsigned char blu_hex[] = {
	0x00, 0x00, 0x2A, 0x22, 0x3C, 0x00, 0x47, 0x50,
	0x5C, 0x80, 0x7A, 0x72, 0x7A, 0x00, 0x00, 0x00,
	0x00, 0x0B, 0x20, 0xAA, 0x6B, 0x8C, 0x00, 0x00,
	0x32, 0x2F, 0x23, 0x00, 0x00, 0x2F, 0x00, 0x00,
	0x22, 0x00, 0x32, 0x90, 0x98, 0x8F, 0x9A, 0x7F,
	0x57, 0xAA, 0x71, 0xAA, 0x4F, 0x80, 0x8B, 0xFF,
	0xFF, 0xFF, 0xD1, 0xD0, 0xCC, 0xEE, 0xD4, 0xE6,
	0xA0, 0xB4, 0xED, 0xFF, 0xFF, 0xE6, 0xEB, 0xFA,
	0x70, 0x80, 0x8B, 0xCD, 0xFF, 0xE1, 0xE2, 0x82,
	0x8B, 0xCD, 0xEE, 0xDB, 0x8B, 0xD3, 0xCC, 0xD3,
	0x80, 0xD8, 0xDD, 0xEE, 0xFF, 0xFF, 0xD6, 0x85,
	0x93, 0x93, 0xB4, 0xC1, 0xCB, 0xD7, 0xDC, 0xC4,
	0xCD, 0xB3, 0xDC, 0xCD, 0xD2, 0xE0, 0x13, 0x2D,
	0x1E, 0x3F, 0x60, 0x87, 0x8C, 0x8F, 0xB5, 0xAD,
	0xB9, 0xE1, 0xF5, 0xE6, 0xE6, 0xD5, 0xEE, 0xFA,
	0x90, 0x99, 0xDE, 0xFA, 0xF0, 0xFF, 0xFF, 0xF0,
	0xF0, 0xFF, 0xFA, 0x00, 0x69, 0x69, 0x80, 0x80,
	0xA9, 0xA9, 0xC0, 0xD3, 0xD3, 0xDC, 0xF5, 0xFF
};


/* This is a list of decimal values representing only the Red portion of the RGB color for each index 
 * entry. There is an entry here for each element of color_names[]. Values are expressed as unsigned char.
 * To use these tables, 'RGB_red = red[CLR_COLOR_NAME]' 
 */
unsigned char red[] = {
	128, 139, 165, 178, 220, 255, 255, 255,
	205, 240, 233, 250, 255, 255, 255, 255,
	255, 184, 218, 238, 189, 240, 128, 255,
	154,  85, 107, 124, 127, 173,   0,   0,
	 34,   0,  50, 144, 152, 143,   0,   0,
	 46, 102,  60,  32,  47,   0,   0,   0,
	  0, 224,   0,  64,  72, 175, 127, 176,
	 95,  70, 100,   0,  30, 173, 135, 135,
	 25,   0,   0,   0,   0,  65, 138,  75,
	 72, 106, 123, 147, 139, 148, 153, 186,
	128, 216, 221, 238, 255, 255, 218, 199,
	219, 255, 255, 255, 255, 250, 245, 255,
	255, 245, 255, 255, 250, 255, 139, 160,
	210, 205, 244, 222, 210, 188, 255, 255,
	255, 255, 255, 250, 253, 255, 255, 245,
	112, 119, 176, 230, 255, 240, 248, 240,
	255, 240, 255,   0, 105, 105, 128, 128,
	169, 169, 192, 211, 211, 220, 245, 255
};

/* This is a list of decimal values representing only the Green portion of the RGB color for each index 
 * entry. There is an entry here for each element of color_names[]. Values are expressed as unsigned char.
 * To use these tables, 'RGB_grn = grn[CLR_COLOR_NAME]' 
 */
unsigned char grn[] = {
	  0,   0,  42,  34,  20,   0,  99, 127,
	 92, 128, 150, 128, 160,  69, 140, 165,
	215, 134, 165, 232, 183, 230, 128, 255,
	205, 107, 142, 252, 255, 255, 100, 128,
	139, 255, 205, 238, 251, 188, 250, 255,
	139, 205, 179, 178,  79, 128, 139, 255,
	255, 255, 206, 224, 209, 238, 255, 224,
	158, 130, 149, 191, 144, 216, 206, 206,
	 25,   0,   0,   0,   0, 105,  43,   0,
	 61,  90, 104, 112,   0,   0,  50,  85,
	  0, 191, 160, 130,   0,   0, 112,  21,
	112,  20, 105, 182, 192, 235, 245, 228,
	235, 222, 248, 250, 250, 255,  69,  82,
	105, 133, 164, 184, 180, 143, 228, 222,
	218, 228, 240, 240, 245, 239, 245, 255,
	128, 136, 196, 230, 250, 248, 248, 255,
	255, 255, 250,   0, 105, 105, 128, 128,
	169, 169, 192, 211, 211, 220, 245, 255
};

/* This is a list of decimal values representing only the Blue portion of the RGB color for each index 
 * entry. There is an entry here for each element of color_names[]. Values are expressed as unsigned char.
 * To use these tables, 'RGB_blu = blu[CLR_COLOR_NAME]' 
 */
unsigned char blu[] = {
	  0,   0,  42,  34,  60,   0,  71,  80,
	 92, 128, 122, 114, 122,   0,   0,   0,
	  0,  11,  32, 170, 107, 140,   0,   0,
	 50,  47,  35,   0,   0,  47,   0,   0,
	 34,   0,  50, 144, 152, 143, 154, 127,
	 87, 170, 113, 170,  79, 128, 139, 255,
	255, 255, 209, 208, 204, 238, 212, 230,
	160, 180, 237, 255, 255, 230, 235, 250,
	112, 128, 139, 205, 255, 225, 226, 130,
	139, 205, 238, 219, 139, 211, 204, 211,
	128, 216, 221, 238, 255, 255, 214, 133,
	147, 147, 180, 193, 203, 215, 220, 196,
	205, 179, 220, 205, 210, 224,  19,  45,
	 30,  63,  96, 135, 140, 143, 181, 173,
	185, 225, 245, 230, 230, 213, 238, 250,
	144, 153, 222, 250, 240, 255, 255, 240,
	240, 255, 250,   0, 105, 105, 128, 128,
	169, 169, 192, 211, 211, 220, 245, 255
};

#endif	// __COLOR_DEFS_H__
