/*
* Copyright (c) 2007 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#pragma once

using namespace System;

#include "../DirectXObject.h"

#include "BlendStateDescription.h"
#include "Enums.h"

namespace SlimDX
{
	namespace Direct3D10
	{	
		ref class Device;
		
		public ref class BlendState : DirectXObject<ID3D10BlendState>
		{
			BlendStateDescription^ m_Description;
		
		internal:
			BlendState( ID3D10BlendState* state );
		
		public:
			~BlendState() { Destruct(); }
			DXOBJECT_FUNCTIONS;

			property bool AlphaToCoverageEnabled
			{
				bool get() { return m_Description->AlphaToCoverageEnabled; }
			}
			
			property ReadOnlyCollection<bool>^ RenderTargetBlendEnabled
			{
				ReadOnlyCollection<bool>^ get() { return m_Description->RenderTargetBlendEnabled; }
			}
			
			property BlendOption SourceBlend
			{
				BlendOption get() { return m_Description->SourceBlend; }
			}
			
			property BlendOption DestinationBlend
			{
				BlendOption get() { return m_Description->DestinationBlend; }
			}
			
			property SlimDX::Direct3D10::BlendOperation BlendOperation
			{
				SlimDX::Direct3D10::BlendOperation get() { return m_Description->BlendOperation; }
			}
			
			property BlendOption SourceAlphaBlend
			{
				BlendOption get() { return m_Description->SourceAlphaBlend; }
			}
			
			property BlendOption DestinationAlphaBlend
			{
				BlendOption get() { return m_Description->DestinationAlphaBlend; }
			}
			
			property SlimDX::Direct3D10::BlendOperation AlphaBlendOperation
			{
				SlimDX::Direct3D10::BlendOperation get() { return m_Description->AlphaBlendOperation; }
			}
			
			property ReadOnlyCollection<ColorWriteMaskFlags>^ RenderTargetWriteMask
			{
				ReadOnlyCollection<ColorWriteMaskFlags>^ get() { return m_Description->RenderTargetWriteMask; }
			}
			
			BlendState( Device^ device, BlendStateDescription^ description );
			
			BlendStateDescription^ CloneDescription();
		};
	}
};