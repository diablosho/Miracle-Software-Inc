

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Nov 17 13:19:50 2014
 */
/* Compiler settings for WIN32DASM.idl:
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


#ifndef __WIN32DASM_h_h__
#define __WIN32DASM_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWIN32DASM_FWD_DEFINED__
#define __IWIN32DASM_FWD_DEFINED__
typedef interface IWIN32DASM IWIN32DASM;

#endif 	/* __IWIN32DASM_FWD_DEFINED__ */


#ifndef __CWIN32DASMDoc_FWD_DEFINED__
#define __CWIN32DASMDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CWIN32DASMDoc CWIN32DASMDoc;
#else
typedef struct CWIN32DASMDoc CWIN32DASMDoc;
#endif /* __cplusplus */

#endif 	/* __CWIN32DASMDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __WIN32DASM_LIBRARY_DEFINED__
#define __WIN32DASM_LIBRARY_DEFINED__

/* library WIN32DASM */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_WIN32DASM;

#ifndef __IWIN32DASM_DISPINTERFACE_DEFINED__
#define __IWIN32DASM_DISPINTERFACE_DEFINED__

/* dispinterface IWIN32DASM */
/* [uuid] */ 


EXTERN_C const IID DIID_IWIN32DASM;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("E170FB6E-2D27-43FE-B739-EDBE47D09CA2")
    IWIN32DASM : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IWIN32DASMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWIN32DASM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWIN32DASM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWIN32DASM * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWIN32DASM * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWIN32DASM * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWIN32DASM * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWIN32DASM * This,
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
    } IWIN32DASMVtbl;

    interface IWIN32DASM
    {
        CONST_VTBL struct IWIN32DASMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWIN32DASM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWIN32DASM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWIN32DASM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWIN32DASM_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWIN32DASM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWIN32DASM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWIN32DASM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IWIN32DASM_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CWIN32DASMDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("D862AE9D-E012-4E1C-8038-C428F70AA430")
CWIN32DASMDoc;
#endif
#endif /* __WIN32DASM_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


