

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Sep 30 00:05:33 2014
 */
/* Compiler settings for x86DASM.idl:
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


#ifndef __x86DASM_h_h__
#define __x86DASM_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Ix86DASM_FWD_DEFINED__
#define __Ix86DASM_FWD_DEFINED__
typedef interface Ix86DASM Ix86DASM;

#endif 	/* __Ix86DASM_FWD_DEFINED__ */


#ifndef __Cx86DASMDoc_FWD_DEFINED__
#define __Cx86DASMDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class Cx86DASMDoc Cx86DASMDoc;
#else
typedef struct Cx86DASMDoc Cx86DASMDoc;
#endif /* __cplusplus */

#endif 	/* __Cx86DASMDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __x86DASM_LIBRARY_DEFINED__
#define __x86DASM_LIBRARY_DEFINED__

/* library x86DASM */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_x86DASM;

#ifndef __Ix86DASM_DISPINTERFACE_DEFINED__
#define __Ix86DASM_DISPINTERFACE_DEFINED__

/* dispinterface Ix86DASM */
/* [uuid] */ 


EXTERN_C const IID DIID_Ix86DASM;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EA876594-F680-4C42-A46F-5FAFF4955832")
    Ix86DASM : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct Ix86DASMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Ix86DASM * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Ix86DASM * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Ix86DASM * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Ix86DASM * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Ix86DASM * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Ix86DASM * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Ix86DASM * This,
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
    } Ix86DASMVtbl;

    interface Ix86DASM
    {
        CONST_VTBL struct Ix86DASMVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ix86DASM_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Ix86DASM_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Ix86DASM_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Ix86DASM_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Ix86DASM_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Ix86DASM_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Ix86DASM_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __Ix86DASM_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Cx86DASMDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("93C1A70C-95B6-4DFC-BCED-D8EB97D94F69")
Cx86DASMDoc;
#endif
#endif /* __x86DASM_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


