#include "Object.h"

Object :: Object(const std::string& fn)
{
    nullify();
    if(!m_Properties.open(fn.c_str()))
    {
        setError("Failed to load object \"" + fn + "\"");
        throw Failure();
    }

    // TODO: once propertylist supports list of elements in group, load all relevant images
    std::string image_path;
    if(m_Properties.getStringValue("images","default",image_path))
        m_vImages.push_back(System::get().imageResources().ensure_shared(
            (std::string)"data/gfx/objects/"+image_path));
    else
    {
        // Note: No default-image sprites are allowed for now
        //setError("Unable to load a default image");
        //throw Failure();
    }
    if(!m_vImages.empty())
        m_Sprite.setImage(m_vImages.front());
}

Object :: ~Object()
{
    
}

