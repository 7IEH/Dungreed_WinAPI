#pragma once
#include "Commoninclude.h"
#include "EHResource.h"

namespace EH
{
	class Resources
	{
	public:
		Resources();
		virtual ~Resources();

		template <typename T>
		static T* Find(const std::wstring& name)
		{
			std::map<std::wstring, Resource*>::iterator iter = mResources.find(name);
			
			if (iter == mResources.end())
			{
				return nullptr;
			}

			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& name, const std::wstring& path)
		{
			T* temp = Resources::Find<T>(name);
			if (temp != nullptr)
			{
				return temp;
			}
		
			temp = new T();
			temp->SetPath(path);
			temp->SetName(name);
			if (FAILED(temp->Load()))
			{
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				delete temp;
				return nullptr;
			}
			mResources.insert(std::make_pair(name, temp));
			
			return temp;
		}

	private:
		static std::map<std::wstring, Resource*> mResources;
	};
}

