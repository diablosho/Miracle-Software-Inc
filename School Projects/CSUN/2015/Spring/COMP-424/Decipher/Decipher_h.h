

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Feb 26 16:45:37 2015
 */
/* Compiler settings for Decipher.idl:
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


#ifndef __Decipher_h_h__
#define __Decipher_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDecipher_FWD_DEFINED__
#define __IDecipher_FWD_DEFINED__
typedef interface IDecipher IDecipher;

#endif 	/* __IDecipher_FWD_DEFINED__ */


#ifndef __Decipher_FWD_DEFINED__
#define __Decipher_FWD_DEFINED__

#ifdef __cplusplus
typedef class Decipher Decipher;
#else
typedef struct Decipher Decipher;
#endif /* __cplusplus */

#endif 	/* __Decipher_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Decipher_LIBRARY_DEFINED__
#define __Decipher_LIBRARY_DEFINED__

/* library Decipher */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Decipher;

#ifndef __IDecipher_DISPINTERFACE_DEFINED__
#define __IDecipher_DISPINTERFACE_DEFINED__

/* dispinterface IDecipher */
/* [uuid] */ 


EXTERN_C const IID DIID_IDecipher;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7A535ACA-EEB6-4A90-89B8-30F9BB0BC787")
    IDecipher : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IDecipherVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDecipher * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDecipher * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDecipher * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IDecipher * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IDecipher * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IDecipher * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IDecipher * This,
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
    } IDecipherVtbl;

    interface IDecipher
    {
        CONST_VTBL struct IDecipherVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDecipher_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDecipher_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDecipher_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDecipher_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IDecipher_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IDecipher_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IDecipher_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IDecipher_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Decipher;

#ifdef __cplusplus

class DECLSPEC_UUID("166E0410-AEF9-4E8C-BEB4-AA845327888E")
Decipher;
#endif
#endif /* __Decipher_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


