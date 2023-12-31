/**********************************************************\ 
Original Author: Richard Bateman (taxilian)

Created:    Oct 29, 2009
License:    Dual license model; choose one of two:
            New BSD License
            http://www.opensource.org/licenses/bsd-license.php
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2009 Richard Bateman, Firebreath development team
\**********************************************************/

#pragma once
#ifndef H_FB_JSAPISIMPLE
#define H_FB_JSAPISIMPLE

#include "JSAPIImpl.h"

namespace FB {
    FB_FORWARD_PTR(JSAPISimple);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class  JSAPISimple
    ///
    /// @brief  Simple JSAPI implementation for those who for whatever reason don't want to use JSAPIAuto
    ///         
    /// @deprecated 1.1.0
    /// @see FB::JSAPIAuto
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class JSAPISimple :
        public FB::JSAPIImpl
    {
    public:
        JSAPISimple(void);
        virtual ~JSAPISimple(void);

    public:
        void getMemberNames(std::vector<std::string> &nameVector) const override;
        size_t getMemberCount() const override;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @fn virtual void registerMethod(std::string name, CallMethodPtr func)
        ///
        /// @brief  Register a method to be exposed to javascript
        ///
        /// All methods exposed to javascript through JSAPISimple must match the FB::CallMethodPtr function
        /// pointer type.  Example:
        /// @code
        ///    registerMethod( "toString", (CallMethodPtr)&JSAPISimple::callToString );
        /// @code
        ///      
        /// This matches the following definition:
        /// @code
        ///      variantPromise callToString(const std::vector<variant>& args);
        /// @endcode
        /// 
        /// @param  name    The name that the method should be exposed to javascript as
        /// @param  func    The function that should be called to handle the javascript method
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void registerMethod(std::string name, CallMethodPtr func);

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @fn virtual void registerProperty(std::string name, GetPropPtr getFunc,
        /// SetPropPtr setFunc)
        ///
        /// @brief  Register a property to be exposed to javascript
        ///
        /// All properties exposed to javascript through JSAPISimple must use getter functions that
        /// match the FB::GetPropPtr type and setter functions that match the FB::SetPropPtr type.
        /// @code
        ///     // read-only
        ///     registerProperty( "valid", (GetPropPtr)&MySimpleAPI::getValid, NULL );
        ///     // -or- write-only
        ///     registerProperty( "valid", NULL, (SetPropPtr)&MySimpleAPI::setValid );
        ///     // -or- read-write
        ///     registerProperty( "valid", (GetPropPtr)&MySimpleAPI::getValid, (SetPropPtr)&MySimpleAPI::setValid);
        /// @code
        ///      
        /// This matches the following definition:
        /// @code
        ///      variantPromise getValid();
        ///      void setValid(variant value);
        /// @endcode
        ///
        /// @param  name    The name. 
        /// @param  getFunc The get function (or NULL for write-only)
        /// @param  setFunc The set function (or NULL for read-only)
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void registerProperty(std::string name, GetPropPtr getFunc, SetPropPtr setFunc);

        // Methods to query existance of members on the API
        virtual bool HasMethod(std::string methodName) const override;
        virtual bool HasProperty(std::string propertyName) const override;
        virtual bool HasProperty(int idx) const override;

        // Methods to manage properties on the API
        virtual variantPromise GetProperty(std::string propertyName) override;
        virtual void SetProperty(std::string propertyName, const variant& value) override; 
        virtual void RemoveProperty(std::string propertyName) override;
        virtual variantPromise GetProperty(int idx) override;
        virtual void SetProperty(int idx, const variant& value) override;
        virtual void RemoveProperty(int idx) override;

        // Methods to manage methods on the API
        virtual variantPromise Invoke(std::string methodName, const std::vector<variant>& args) override;

    public:

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @fn virtual variantPromise callFireEvent(const std::vector<variant>& args)
        ///
        /// @brief  Example function for testing fireEvent
        ///
        /// @param  args    arguments from javascript.  The first should be the name of the event
        ///                 to fire, the rest will be passed into the event 
        ///
        /// @return nothing
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual variantPromise callFireEvent(const std::vector<variant>& args_in);

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @fn virtual variantPromise callToString(const std::vector<variant>& args)
        ///
        /// @brief  Called when a string representation of the object requested.  Always returns
        ///         "JSAPI Javascript Object";  
        ///
        /// @param  args   All arguments are ignored
        ///
        /// @return "JSAPI Javascript Object"
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual variantPromise callToString(const std::vector<variant>& args);

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @fn virtual variantPromise getValid()
        ///
        /// @brief  Returns true to indicate that the JSAPI interface is working
        ///
        /// @return true 
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual variantPromise getValid();

    protected:
        MethodMap m_methodMap;
        PropertyMap m_propertyMap;
        bool m_allowRemoveProperty;
    };

};

#endif

