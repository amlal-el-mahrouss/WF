#ifdef __OBJC__

#import <Foundation/Foundation.h>

//! Project version number for WF.
FOUNDATION_EXPORT double WFVersionNumber;

//! Project version string for WF.
FOUNDATION_EXPORT const unsigned char WFVersionString[];

#import <WF/HTTPObject.h>

#else
#pragma once
#include <WF/CHTTP.h>
#endif

