#ifndef _RESOURCEMAP_H
#define _RESOURCEMAP_H

#include <map>
#include <memory>

template<class T>
class ResourceMap : public IFallible
{
private:

	std::map<std::string, std::shared_ptr<T>> m_Resources;

public:

	ResourceMap() {}
	virtual ~ResourceMap() {}

	unsigned int size() { return m_Resources.size(); }
	bool empty() const { return m_Resources.empty(); }

	bool add(std::string name, T* resource) {
		if(m_Resources.find(name) == m_Resources.end()){
			m_Resources[name].reset(resource);
			return true;
		}
		return false;
	}

	T* ensure(std::string name) {
		typename std::map<std::string, std::shared_ptr<T>>::iterator itr;
		if((itr = m_Resources.find(name)) == m_Resources.end()) {
            T* r = new T(name);
			m_Resources[name].reset(r);
			return r;
		}
		return itr->second.get();
	}

	std::shared_ptr<T> ensure_shared(std::string name) {
		typename std::map<std::string, std::shared_ptr<T>>::iterator itr;
		if((itr = m_Resources.find(name)) == m_Resources.end()) {
            T* r = new T(name);
			m_Resources[name].reset(r);
			return m_Resources[name];
		}
		return itr->second;
	}

	void remove(std::string name) {
		for(auto itr = m_Resources.begin();
			itr != m_Resources.end();
			++itr)
		{
			if(itr->first == name) {
				//delete itr->second;
				m_Resources.erase(itr);
				break;
			}
		}
	}

	T* get(std::string name) {
		typename std::map<std::string, std::shared_ptr<T>> itr;
		if((itr = m_Resources.find(name)) == m_Resources.end())
			return NULL;
		return itr->second.get();
	}

	std::shared_ptr<T> get_shared(std::string name) {
		typename std::map<std::string, std::shared_ptr<T>> itr;
		if((itr = m_Resources.find(name)) == m_Resources.end())
			return NULL;
		return itr->second;
	}

	void clear(){
		//for(auto itr = m_Resources.begin();
		//    itr != m_Resources.end();
		//    ++itr)
		//{
		//    delete itr->second;
		//}
		m_Resources.clear();
	}
};

#endif

