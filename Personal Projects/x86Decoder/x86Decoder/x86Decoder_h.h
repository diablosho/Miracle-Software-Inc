

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Nov 17 13:19:01 2014
 */
/* Compiler settings for x86Decoder.idl:
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


#ifndef __x86Decoder_h_h__
#define __x86Decoder_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __Ix86Decoder_FWD_DEFINED__
#define __Ix86Decoder_FWD_DEFINED__
typedef interface Ix86Decoder Ix86Decoder;

#endif 	/* __Ix86Decoder_FWD_DEFINED__ */


#ifndef __Cx86DecoderDoc_FWD_DEFINED__
#define __Cx86DecoderDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class Cx86DecoderDoc Cx86DecoderDoc;
#else
typedef struct Cx86DecoderDoc Cx86DecoderDoc;
#endif /* __cplusplus */

#endif 	/* __Cx86DecoderDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __x86Decoder_LIBRARY_DEFINED__
#define __x86Decoder_LIBRARY_DEFINED__

/* library x86Decoder */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_x86Decoder;

#ifndef __Ix86Decoder_DISPINTERFACE_DEFINED__
#define __Ix86Decoder_DISPINTERFACE_DEFINED__

/* dispinterface Ix86Decoder */
/* [uuid] */ 


EXTERN_C const IID DIID_Ix86Decoder;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("EFBBCEA4-0BAC-4206-9374-FC501F356050")
    Ix86Decoder : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct Ix86DecoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Ix86Decoder * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Ix86Decoder * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Ix86Decoder * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Ix86Decoder * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Ix86Decoder * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Ix86Decoder * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Ix86Decoder * This,
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
    } Ix86DecoderVtbl;

    interface Ix86Decoder
    {
        CONST_VTBL struct Ix86DecoderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ix86Decoder_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Ix86Decoder_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Ix86Decoder_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Ix86Decoder_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Ix86Decoder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Ix86Decoder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Ix86Decoder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __Ix86Decoder_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Cx86DecoderDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("84346B18-F0CE-4E3D-AE5E-7D6FFE62A8A8")
Cx86DecoderDoc;
#endif
#endif /* __x86Decoder_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


