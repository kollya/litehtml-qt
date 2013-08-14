#include "html.h"
#include "el_tr.h"


litehtml::el_tr::el_tr( litehtml::document* doc ) : html_tag(doc)
{

}

litehtml::el_tr::~el_tr()
{

}

void litehtml::el_tr::finish()
{
	const tchar_t* str = get_attr(_t("align"));
	if(str)
	{
		m_style.add_property(_t("text-align"), str, 0, false);
	}
	str = get_attr(_t("valign"));
	if(str)
	{
		m_style.add_property(_t("vertical-align"), str, 0, false);
	}
	html_tag::finish();
}

void litehtml::el_tr::get_inline_boxes( position::vector& boxes )
{
	position pos;
	for(elements_vector::iterator iter = m_children.begin(); iter != m_children.end(); iter++)
	{
		element* el = (*iter);
		if(el->get_display() == display_table_cell)
		{
			pos.x		= el->left() + el->margin_left();
			pos.y		= el->top() - m_padding.top - m_borders.top;

			pos.width	= el->right() - pos.x - el->margin_right() - el->margin_left();
			pos.height	= el->height() + m_padding.top + m_padding.bottom + m_borders.top + m_borders.bottom;

			boxes.push_back(pos);
		}
	}
}