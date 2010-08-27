//
//  GTMServiceManagement.h
//
//  Copyright 2010 Google Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License"); you may not
//  use this file except in compliance with the License.  You may obtain a copy
//  of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
//  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
//  License for the specific language governing permissions and limitations under
//  the License.
//

#include <launch.h>
#include <CoreFoundation/CoreFoundation.h>
#include "GTMDefines.h"

GTM_EXTERN_C_BEGIN

// Done in C as opposed to Objective-C as lots of services may not want
// to bring in Obj-C libraries.

// For rough documentation on these methods please see
// <ServiceManagement/ServiceManagement.h> from the 10.6 sdk.
// This reimplements some of the ServiceManagement framework on 10.4 and 10.5.
// (not tested on 10.4, but should work YMMV).
// Caller takes ownership of error if necessary.

Boolean GTMSMJobSubmit(CFDictionaryRef job, CFErrorRef *error);
Boolean GTMSMJobRemove(CFStringRef jobLabel, CFErrorRef *error);

// Caller takes ownership of the returned type.
// Note that the dictionary returned will have 0 for machports.
// To get a machport, use bootstrap_look_up, or NSMachBootstrapServer.
CFDictionaryRef GTMSMJobCopyDictionary(CFStringRef jobLabel);

// This one is conspiciously absent from the ServiceManagement framework.
// Performs a check-in for the running process and returns its dictionary with
// the appropriate sockets and machports filled in.
// Caller  takes ownership of the returned type.
CFDictionaryRef GTMSMJobCheckIn(CFErrorRef *error);

// The official ServiceManagement version returns an array of job dictionaries.
// This returns a dictionary of job dictionaries where the key is the label
// of the job, and the value is the dictionary for the job of that label.
// Caller takes ownership of the returned type.
CFDictionaryRef GTMSMCopyAllJobDictionaries(void);


// Convert a CFType (and any of it's subitems) into a launch_data_t.
// Caller takes ownership of the returned type if it isn't added to a launch
// data container type.
launch_data_t GTMLaunchDataCreateFromCFType(CFTypeRef cf_type_ref,
                                            CFErrorRef *error);

// Convert a launch_data_t (and any of it's subitems) into a CFType.
// If |convert_non_standard_objects| is true, file descriptors and machports
// will be included in the returned dictionary, otherwise they will be ignored.
// Caller is takes ownership of the returned type.
CFTypeRef GTMCFTypeCreateFromLaunchData(launch_data_t ldata,
                                        bool convert_non_standard_objects,
                                        CFErrorRef *error);

GTM_EXTERN_C_END
