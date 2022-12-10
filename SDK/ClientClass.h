/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __CLIENTCLASS_H__
#define __CLIENTCLASS_H__


namespace Valve
{
	class RecvTable;
	class ClientClass;
	class RecvProp;
	class CRecvProxyData;
	class DVariant;
	typedef void (__cdecl *RecvVarProxyFn)( const CRecvProxyData *pData, void *pStruct, void *pOut );

	class DVariant
	{
	public:
		union
		{
			float	m_Float;
			int		m_Int;
			const char	*m_pString;
			void	*m_pData;
			float	m_Vector[3];
		};
		int	m_Type;
	};

	class CRecvProxyData
	{
	public:
		const RecvProp	*m_pRecvProp;
		DVariant		m_Value;
		int				m_iElement;
		int				m_ObjectID;
	};
	class RecvProp
	{
	public:
		const char* m_pVarName;
		int	m_RecvType;
		int m_Flags;
		int m_StringBufferSize;
		bool m_bInsideArray;
		const void *m_pExtraData;
		RecvProp* m_pArrayProp;
		void* m_ArrayLengthProxy;
		RecvVarProxyFn m_ProxyFn;
		void* m_DataTableProxyFn;
		RecvTable* m_pDataTable;
		int m_Offset;
		int m_ElementStride;
		int m_nElements;
		const char* m_pParentArrayPropName;
	};

	class RecvTable
	{
	public:
		RecvProp* m_pProps;
		int m_nProps;
		void* m_pDecoder;
		const char* m_pNetTableName;
		bool			m_bInitialized;
		bool			m_bInMainList;
	};

	class ClientClass
	{
	public:
		void* m_pCreateFn;
		void* m_pCreateEventFn;
		char* m_pNetworkName;
		RecvTable* m_pRecvTable;
		ClientClass* m_pNext;
		int m_ClassID;
	};
};


#endif //__CLIENTCLASS_H__