/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#import "MacOsHelper.h"
#import <ServiceManagement/ServiceManagement.h>

static NSString *const kLauncherIdentifier =
    @"com.example.CalcWidgetLauncher";

static SMAppService *loginItemService() {
    return [SMAppService
        loginItemServiceWithIdentifier:kLauncherIdentifier];
}

bool registerLoginItem() {
    NSError *error = nil;
    BOOL result = [loginItemService() registerAndReturnError:&error];

    if (!result && error) {
        NSLog(@"Failed to register login item: %@",
              error);
    }

    return result;
}

bool unregisterLoginItem() {
    NSError *error = nil;

    BOOL result = [loginItemService()
        unregisterAndReturnError:&error];

    if (!result && error) {
        NSLog(@"Failed to unregister login item: %@",
              error);
    }

    return result;
}

bool isLoginItemEnabled() {
    return loginItemService().status == SMAppServiceStatusEnabled;
}

bool MacOsHelper::setAutostart(bool enabled) {
    if(enabled) {
        return registerLoginItem();
    } else {
        return unregisterLoginItem();
    }
}