

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Sep 30 00:05:34 2014
 */
/* Compiler settings for Win32DASM.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __Win32DASM_h_h__
#define __Win32DASM_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWin32DASM_FWD_DEFINED__
#define __IWin32DASM_FWD_DEFINED__
typedef interface IWin32DASM IWin32DASM;

#endif 	/* __IWin32DASM_FWD_DEFINED__ */


#ifndef __CWin32DASMDoc_FWD_DEFINED__
#define __CWin32DASMDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CWin32DASMDoc CWin32DASMDoc;
#else
typedef struct CWin32DASMDoc CWin32DASMDoc;
#endif /* __cplusplus */

#endif 	/* __CWin32DASMDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Win32DASM_LIBRARY_DEFINED__
#define __Win32DASM_LIBRARY_DEFINED__

/* library Win32DASM */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Win32DASM;

#ifndef __IWin32DASM_DISPINTERFACE_DEFINED__
#define __IWin32DASM_DISPINTERFACE_DEFINED__

/* dispinterface IWin32DASM */
/* [uuid] */ 


EXTERN_C const IID DIID_IWin32DASM;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("82B4A7EC-F6E5-4AE6-A741-A1C340CFC6B4")
    IWin32DASM : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IWin32DASMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWin32DASM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWin32DASM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWin32DASM * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWin32DASM * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWin32DASM * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWin32DASM * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWin32DASM * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IWin32DASMVtbl;

    interface IWin32DASM
    {
        CONST_VTBL struct IWin32DASMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWin32DASM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWin32DASM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWin32DASM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWin32DASM_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWin32DASM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWin32DASM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWin32DASM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IWin32DASM_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CWin32DASMDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("6EA726A9-F237-4DD9-91C7-96414EF67028")
CWin32DASMDoc;
#endif
#endif /* __Win32DASM_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


