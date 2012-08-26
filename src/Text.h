#ifndef _TEXT_H
#define _TEXT_H

#include <string>
#include <memory>
#include "Font.h"
#include "Sprite.h"
#include "math/vector2.h"
#include "Graphics.h"
#include "IDepthSortable.h"
#include "IMovable.h"

class Text:
    public IDepthSortable,
    virtual public IMovable,
    virtual public IRenderable
{
    private:
        void nullify() {
            m_bVisible = true;
            depth(0.0f);
        }
        std::shared_ptr<Font> m_spFont;
        std::string m_sText;
        Color m_Color;
        int m_Align;
        bool m_bVisible;

    public:
        Text(std::shared_ptr<Font>& font, const std::string& text, const Vector2 pos = Vector2(), Color c = Color(), int align = -1):
            m_spFont(font),
            m_sText(text),
            m_Color(c),
            m_Align(align)
        {
            nullify();
        }

        bool visible() const { return m_bVisible; }
        void visible(bool b = true) { m_bVisible = b; }

        virtual void render() const;
        virtual ~Text() {
        }

        const std::string& text() const { return m_sText; }
        void text(std::string text) { m_sText = text; }

        Color color() const { return m_Color; }
        void color(Color c) { m_Color = c; }
};

#endif

