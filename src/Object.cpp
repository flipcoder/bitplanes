#include "Object.h"

Object :: Object(const std::string& fn)
{
    nullify();

    std::string ext = FileSystem::getExtension(fn);
    if(ext=="ini") // load as properties
    {
        if(!m_Properties.open(fn.c_str()))
        {
            setError("Failed to load object \"" + fn + "\"");
            throw Failure();
        }

        m_spSprite.reset(new Sprite());
        
        // TODO: once propertylist supports list of elements in group, load all relevant images
        //  otherwise, load default
        std::string image_path;
        if(m_Properties.getStringValue("images","default",image_path)) {
            m_vImages.push_back(System::get().imageResources().ensure_shared(
                (std::string)"data/gfx/objects/"+image_path));
        }
        else
        {
            // Note: No default-image sprites are allowed for now
            //setError("Unable to load a default image");
            //throw Failure();
        }
    }
    else // load as image with default properties
    {
        m_spSprite.reset(new Sprite(fn));
    }

    if(!m_vImages.empty())
        m_spSprite->setImage(m_vImages.front());
}

Object :: ~Object()
{
    
}

