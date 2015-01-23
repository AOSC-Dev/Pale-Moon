/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "prprf.h"
#include "prmem.h"
#include "nsCOMPtr.h"
#include "nsStringGlue.h"
#include "nsIStringBundle.h"
#include "nsImapStringBundle.h"
#include "nsIServiceManager.h"
#include "nsIURI.h"
#include "nsServiceManagerUtils.h"
#include "mozilla/Services.h"

#define IMAP_MSGS_URL       "chrome://messenger/locale/imapMsgs.properties"

extern "C" 
nsresult
IMAPGetStringByName(const char* stringName, PRUnichar **aString)
{
  nsCOMPtr <nsIStringBundle> sBundle;
  nsresult rv = IMAPGetStringBundle(getter_AddRefs(sBundle));
  if (NS_SUCCEEDED(rv) && sBundle)
    rv = sBundle->GetStringFromName(NS_ConvertASCIItoUTF16(stringName).get(),
                                    aString);
  return rv;
}

nsresult
IMAPGetStringBundle(nsIStringBundle **aBundle)
{
  nsresult rv=NS_OK;
  nsCOMPtr<nsIStringBundleService> stringService =
    mozilla::services::GetStringBundleService();
  if (!stringService) return NS_ERROR_NULL_POINTER;
  nsCOMPtr<nsIStringBundle> stringBundle;
  rv = stringService->CreateBundle(IMAP_MSGS_URL, getter_AddRefs(stringBundle));
  *aBundle = stringBundle;
  NS_IF_ADDREF(*aBundle);
  return rv;
}
