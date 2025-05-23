#include "BasePopup.h"

#include "ui_legacy/theme/Style.h"

namespace game {
namespace frontend {
namespace ui_legacy {
namespace style {

void BasePopup::AddStyles() {

	SetPrefix( "BP" );

	// general style

	/*AddStyle(
		"", SH() {
			s->Set( ::ui_legacy::A_ALIGN, ::ui_legacy::ALIGN_HCENTER | ::ui_legacy::ALIGN_BOTTOM );
			s->Set( ::ui_legacy::A_Z_INDEX, 0.7f );
		}
	);*/

	// hacks
	// TODO: fix properly
	const int8_t
		ftop = -2,
		fleft = -5,
		fright = -5,
		fwidth = 12,
		fheight = 12;

	AddStyle(
		"Governor", SH() {
			s->Set( ::ui_legacy::A_TOP, 3 + ftop );
			s->Set( ::ui_legacy::A_LEFT, 3 + fleft );
			s->Set( ::ui_legacy::A_RIGHT, 3 + fright );
			s->Set( ::ui_legacy::A_HEIGHT, 26 + fheight );
		}
	);

	AddStyle(
		"Nutrients", SH() {
			s->Set( ::ui_legacy::A_TOP, 32 + ftop );
			s->Set( ::ui_legacy::A_LEFT, 3 + fleft );
			s->Set( ::ui_legacy::A_WIDTH, 136 + fwidth );
			s->Set( ::ui_legacy::A_HEIGHT, 154 + fheight );
		}
	);

	AddStyle(
		"Commerce", SH() {
			s->Set( ::ui_legacy::A_TOP, 189 + ftop );
			s->Set( ::ui_legacy::A_LEFT, 3 + fleft );
			s->Set( ::ui_legacy::A_WIDTH, 136 + fwidth );
			s->Set( ::ui_legacy::A_HEIGHT, 194 + fheight );
		}
	);

	AddStyle(
		"GlobalInfo", SH() {
			s->Set( ::ui_legacy::A_TOP, 386 + ftop );
			s->Set( ::ui_legacy::A_LEFT, 3 + fleft );
			s->Set( ::ui_legacy::A_WIDTH, 136 + fwidth );
			s->Set( ::ui_legacy::A_HEIGHT, 56 + fheight );
		}
	);

	AddStyle(
		"CenterArea", SH() {
			s->Set( ::ui_legacy::A_TOP, 32 + ftop );
			s->Set( ::ui_legacy::A_LEFT, 142 + fleft );
			s->Set( ::ui_legacy::A_RIGHT, 142 + fright );
			s->Set( ::ui_legacy::A_HEIGHT, 226 + fheight );
		}
	);

	AddStyle(
		"CenterAreaPage", SH() {
			s->Set( ::ui_legacy::A_BOTTOM, 26 );
		}
	);

	AddStyle(
		"CenterAreaResourceTile", SH() {
			s->Set( ::ui_legacy::A_ALIGN, ::ui_legacy::ALIGN_LEFT | ::ui_legacy::ALIGN_TOP );
			s->Set( ::ui_legacy::A_WIDTH, 96 );
			s->Set( ::ui_legacy::A_HEIGHT, 48 );
		}
	);

	AddStyle(
		"CenterAreaResourceSprite", SH() {
			s->Set( ::ui_legacy::A_ALIGN, ::ui_legacy::ALIGN_LEFT | ::ui_legacy::ALIGN_TOP );
			s->Set( ::ui_legacy::A_WIDTH, 100 );
			s->Set( ::ui_legacy::A_HEIGHT, 68 );
		}
	);

	AddStyle(
		"Yields", SH() {
			s->Set( ::ui_legacy::A_TOP, 261 + ftop );
			s->Set( ::ui_legacy::A_LEFT, 142 + fleft );
			s->Set( ::ui_legacy::A_RIGHT, 3 + fright );
			s->Set( ::ui_legacy::A_HEIGHT, 89 + fheight );
		}
	);

	AddStyle(
		"Energy", SH() {
			s->Set( ::ui_legacy::A_TOP, 353 + ftop );
			s->Set( ::ui_legacy::A_LEFT, 142 + fleft );
			s->Set( ::ui_legacy::A_RIGHT, 3 + fright );
			s->Set( ::ui_legacy::A_HEIGHT, 89 + fheight );
		}
	);

	AddStyle(
		"Facilities", SH() {
			s->Set( ::ui_legacy::A_TOP, 32 + ftop );
			s->Set( ::ui_legacy::A_LEFT, 539 + fleft );
			s->Set( ::ui_legacy::A_RIGHT, 3 + fright );
			s->Set( ::ui_legacy::A_HEIGHT, 226 + fheight );
		}
	);

	AddStyle(
		"Buttons", SH() {
			s->Set( ::ui_legacy::A_TOP, 445 + ftop );
			s->Set( ::ui_legacy::A_LEFT, 104 + fleft );
			s->Set( ::ui_legacy::A_RIGHT, 104 + fright );
			s->Set( ::ui_legacy::A_HEIGHT, 26 + fheight );
		}
	);

}

}
}
}
}
