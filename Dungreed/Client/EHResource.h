#pragma once
#include "Commoninclude.h"
#include "EHEntity.h"

namespace EH
{
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load() = 0;

		void SetPath(const std::wstring& path) { mPath = path; }
		std::wstring& GetPath() { return mPath; }

	private:
		std::wstring mPath;
	};
}
