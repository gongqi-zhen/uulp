#define BAR_SYMBOL		'|'
#define BAR_TOP_Y			5
#define BAR_BOTTOM_Y	15
#define BAR_STOP			0
#define BAR_DOWN			1
#define BAR_UP				-1

struct bar {
	  int top_y, bottom_y;
	  int dir;
};

