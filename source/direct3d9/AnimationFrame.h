/*
* Copyright (c) 2007-2008 SlimDX Group
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

#include "XFile.h"

namespace SlimDX
{
	namespace Direct3D9
	{
		ref class MeshContainer;
		ref class Frame;
		ref class AnimationController;

		public enum class MeshDataType : System::Int32
		{
			Mesh = D3DXMESHTYPE_MESH,
			ProgressiveMesh = D3DXMESHTYPE_PMESH,
			PatchMesh = D3DXMESHTYPE_PATCHMESH
		};

		public ref class MeshData
		{
		private:
			MeshDataType type;
			Mesh^ mesh;
			ProgressiveMesh^ progressiveMesh;
			PatchMesh^ patchMesh;

		public:
			MeshData( Mesh^ mesh );
			MeshData( ProgressiveMesh^ mesh );
			MeshData( PatchMesh^ mesh );

			property MeshDataType Type
			{
				MeshDataType get() { return type; }
			}

			property Mesh^ Mesh
			{
				SlimDX::Direct3D9::Mesh^ get() { return mesh; }
				void set( SlimDX::Direct3D9::Mesh^ value );
			}

			property ProgressiveMesh^ ProgressiveMesh
			{
				SlimDX::Direct3D9::ProgressiveMesh^ get() { return progressiveMesh; }
				void set( SlimDX::Direct3D9::ProgressiveMesh^ value );
			}

			property PatchMesh^ PatchMesh
			{
				SlimDX::Direct3D9::PatchMesh^ get() { return patchMesh; }
				void set( SlimDX::Direct3D9::PatchMesh^ value );
			}
		};

		class MeshContainerShim : public D3DXMESHCONTAINER
		{
		private:
			gcroot<MeshContainer^> m_Container;

		public:
			MeshContainerShim( MeshContainer^ container );

			MeshContainer^ GetMeshContainer()
			{
				return m_Container;
			}
		};

		public ref class MeshContainer abstract
		{
		internal:
			property D3DXMESHCONTAINER *Pointer;

			void Destruct();

			System::String^ m_Name;
			MeshContainer^ m_NextContainer;
			MeshData^ m_MeshData;
			SkinInfo^ m_SkinInfo;

		protected:
			MeshContainer();

		public:
			virtual ~MeshContainer();
			!MeshContainer();

			array<ExtendedMaterial>^ GetMaterials();
			void SetMaterials( array<ExtendedMaterial>^ materials );

			array<EffectInstance>^ GetEffects();
			void SetEffects( array<EffectInstance>^ effects );

			array<int>^ GetAdjacency();
			void SetAdjacency( array<int>^ adjacency );

			property System::String^ Name
			{
				System::String^ get();
				void set( System::String^ value );
			}

			property MeshData^ Mesh
			{
				MeshData^ get();
				void set( MeshData^ value );
			}

			property SkinInfo^ SkinInfo
			{
				SlimDX::Direct3D9::SkinInfo^ get();
				void set( SlimDX::Direct3D9::SkinInfo^ value );
			}

			property MeshContainer^ NextMeshContainer
			{
				MeshContainer^ get();
				void set( MeshContainer^ value );
			}
		};

		public interface struct IAllocateHierarchy
		{
			virtual MeshContainer^ CreateMeshContainer( System::String^ name, MeshData^ meshData, array<ExtendedMaterial>^ materials, array<EffectInstance>^ effectInstances, array<int>^ adjacency, SkinInfo^ skinInfo ) = 0;
			virtual Frame^ CreateFrame( System::String^ name ) = 0;
			virtual void DestroyFrame( Frame^ frame ) = 0;
			virtual void DestroyMeshContainer( MeshContainer^ container ) = 0;
		};
		
		public interface struct ILoadUserData
		{
			virtual void LoadFrameData( Frame^ frame, XFileData^ data ) = 0;
			virtual void LoadMeshData( MeshContainer^ meshContainer, XFileData^ data ) = 0;
			virtual void LoadTopLevelData( XFileData^ data ) = 0;
		};

		public interface struct ISaveUserData
		{
			virtual void AddFrameChildData( Frame^ frame, XFileSaveObject^ saveObject, XFileSaveData^ saveData );
			virtual void AddMeshChildData( MeshContainer^ meshContainer, XFileSaveObject^ saveObject, XFileSaveData^ saveData );
			virtual void AddTopLevelDataPost( XFileSaveObject^ saveObject );
			virtual void AddTopLevelDataPre( XFileSaveObject^ saveObject );
			virtual void RegisterTemplates( XFile^ xfile );
			virtual void SaveTemplates( XFileSaveObject^ saveObject );
		};

		class IAllocateHierarchyShim : public ID3DXAllocateHierarchy
		{
		private:
			gcroot<IAllocateHierarchy^> m_WrappedInterface;

		public:
			IAllocateHierarchyShim( IAllocateHierarchy^ wrappedInterface );

			HRESULT WINAPI CreateFrame( LPCSTR Name, LPD3DXFRAME *ppNewFrame );
			HRESULT WINAPI CreateMeshContainer( LPCSTR Name, const D3DXMESHDATA *pMeshData, const D3DXMATERIAL *pMaterials, const D3DXEFFECTINSTANCE *pEffectInstances, DWORD NumMaterials, const DWORD *pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER *ppNewMeshContainer );
			HRESULT WINAPI DestroyFrame( LPD3DXFRAME pFrameToFree );
			HRESULT WINAPI DestroyMeshContainer( LPD3DXMESHCONTAINER pMeshContainerToFree );
		};

		class ILoadUserDataShim : public ID3DXLoadUserData
		{
		private:
			gcroot<ILoadUserData^> m_WrappedInterface;

		public:
			ILoadUserDataShim( ILoadUserData^ wrappedInterface );

			HRESULT WINAPI LoadFrameChildData( LPD3DXFRAME pFrame, LPD3DXFILEDATA pXofChildData );
			HRESULT WINAPI LoadMeshChildData( LPD3DXMESHCONTAINER pMeshContainer, LPD3DXFILEDATA pXofChildData );
			HRESULT WINAPI LoadTopLevelData( LPD3DXFILEDATA pXofChildData );
		};

		class ISaveUserDataShim : public ID3DXSaveUserData
		{
		private:
			gcroot<ISaveUserData^> m_WrappedInterface;

		public:
			ISaveUserDataShim( ISaveUserData^ wrappedInterface );

			HRESULT WINAPI AddFrameChildData( const D3DXFRAME *pFrame, LPD3DXFILESAVEOBJECT pXofSave, LPD3DXFILESAVEDATA pXofFrameData );
			HRESULT WINAPI AddMeshChildData( const D3DXMESHCONTAINER *pMeshContainer, LPD3DXFILESAVEOBJECT pXofSave, LPD3DXFILESAVEDATA pXofMeshData );
			HRESULT WINAPI AddTopLevelDataObjectsPost( LPD3DXFILESAVEOBJECT pXofSave );
			HRESULT WINAPI AddTopLevelDataObjectsPre( LPD3DXFILESAVEOBJECT pXofSave );
			HRESULT WINAPI RegisterTemplates( LPD3DXFILE pXFileApi );
			HRESULT WINAPI SaveTemplates( LPD3DXFILESAVEOBJECT pXofSave );
		};

		class FrameShim : public D3DXFRAME
		{
		private:
			gcroot<Frame^> m_Frame;

		public:
			FrameShim( Frame^ frame );
			FrameShim( Frame^ frame, const D3DXFRAME &pFrame );

			Frame^ GetFrame()
			{
				return m_Frame;
			}
		};

		public ref class Frame abstract
		{
		internal:
			property D3DXFRAME *Pointer;

			void Destruct();

			System::String^ m_Name;
			Frame^ m_FirstChild;
			Frame^ m_Sibling;
			MeshContainer^ m_MeshContainer;

			static Frame^ BuildHierarchyFromUnmanaged( FrameShim* pFrame );
			static void BuildManagedFrames( Frame^% frame, FrameShim* pFrame );
			static void BuildManagedMeshes( MeshContainer^% mesh, MeshContainerShim* pMesh );
			static void RegisterAnimations( Frame^ frame, LPD3DXANIMATIONCONTROLLER animation );

			static FrameShim* BuildHierarchyFromManaged( Frame^ frame );
			static void BuildUnmanagedFrames( FrameShim*% pFrame, Frame^ frame );
			static void BuildUnmanagedMeshes( MeshContainerShim*% pMesh, MeshContainer^ mesh );

		protected:
			Frame();

		public:
			virtual ~Frame();
			!Frame();

			static Frame^ LoadHierarchyFromX( Device^ device, System::String^ fileName, MeshFlags options, IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController );
			static Frame^ LoadHierarchyFromX( Device^ device, array<System::Byte>^ memory, MeshFlags options, IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController );
			static Frame^ LoadHierarchyFromX( Device^ device, System::IO::Stream^ stream, MeshFlags options, IAllocateHierarchy^ allocator, ILoadUserData^ userDataLoader, [Out] AnimationController^% animationController );

			static Result SaveHierarchyToFile( System::String^ fileName, XFileFormat format, Frame^ root, AnimationController^ animationController, ISaveUserData^ userDataSaver );
			static Result SaveHierarchyToFile( System::String^ fileName, XFileFormat format, Frame^ root, AnimationController^ animationController );

			Frame^ FindChild( System::String^ name );
			void AppendChild( Frame^ child );

			static BoundingSphere CalculateBoundingSphere( Frame^ root );
			static Result DestroyHierarchy( Frame^ root, IAllocateHierarchy^ allocator );
			static int CountNamedFrames( Frame^ root );
			static void RegisterNamedMatrices( Frame^ root, AnimationController^ controller );

			property System::String^ Name
			{
				System::String^ get();
				void set( System::String^ value );
			}

			property Matrix TransformationMatrix
			{
				Matrix get();
				void set( Matrix value );
			}

			property MeshContainer^ MeshContainer
			{
				SlimDX::Direct3D9::MeshContainer^ get();
				void set( SlimDX::Direct3D9::MeshContainer^ value );
			}

			property Frame^ Sibling
			{
				Frame^ get();
				void set( Frame^ value );
			}

			property Frame^ FirstChild
			{
				Frame^ get();
				void set( Frame^ value );
			}
		};
	}
}