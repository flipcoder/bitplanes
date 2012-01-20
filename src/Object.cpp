#include "Object.h"

Object :: Object(const std::string& fn):
    IConfig(fn)
{
    nullify();

    if(FileSystem::hasExtension(fn,"ini")) // load as properties
    {
        m_spSprite.reset(new Sprite());

        PropertyList::Group* imagelist = properties().getGroup("images");
        for(auto img = imagelist->cbegin();
            img != imagelist->cend();
            img++)
        {
            m_Images[img->first] = System::get().imageResources().ensure_shared((std::string)"data/gfx/objects/"+img->second);
        }
        //if(properties().getStringValue("images","default",image_path)) {
        //    m_vImages.push_back(System::get().imageResources().ensure_shared(
        //        (std::string)"data/gfx/objects/"+image_path));
        //}
        //else
        //{
            // Note: No default-image sprites are allowed for now
            //setError("Unable to load a default image");
            //throw Failure();
        //}
        m_spSprite->setImage(image("default")); // may be null
    }
    else // load as image with default properties
    {
        m_spSprite.reset(new Sprite(fn));
    }
}

Object :: ~Object()
{
    
}

