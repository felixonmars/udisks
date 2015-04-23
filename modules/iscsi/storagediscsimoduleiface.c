/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2015 Peter Hatina <phatina@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "config.h"

#include <modules/storagedmoduleiface.h>

#include <storaged/storaged-generated.h>
#include <src/storageddaemon.h>
#include <src/storagedmodulemanager.h>
#include <src/storagedlogging.h>

#include "storagediscsitypes.h"
#include "storagediscsistate.h"

#include "storagedlinuxmanageriscsiinitiator.h"

/* ---------------------------------------------------------------------------------------------------- */

gpointer
storaged_module_init (gchar **module_id)
{
  *module_id = g_strdup (ISCSI_MODULE_NAME);

  return storaged_iscsi_state_new ();
}

/* ---------------------------------------------------------------------------------------------------- */

StoragedModuleInterfaceInfo **
storaged_module_get_block_object_iface_setup_entries (void)
{
  return NULL;
}

/* ---------------------------------------------------------------------------------------------------- */

StoragedModuleInterfaceInfo **
storaged_module_get_drive_object_iface_setup_entries (void)
{
  return NULL;
}

/* ---------------------------------------------------------------------------------------------------- */

StoragedModuleObjectNewFunc *
storaged_module_get_object_new_funcs (void)
{
  StoragedModuleObjectNewFunc *funcs = NULL;

  /* TODO: Add object_new funcs */
  /* funcs = g_new0 (StoragedModuleObjectNewFunc, 2); */

  return funcs;
}

/* ---------------------------------------------------------------------------------------------------- */

static GDBusInterfaceSkeleton *
new_manager_initiator_iface (StoragedDaemon *daemon)
{
  StoragedLinuxManagerISCSIInitiator *manager;

  manager = storaged_linux_manager_iscsi_initiator_new (daemon);

  return G_DBUS_INTERFACE_SKELETON (manager);
}

StoragedModuleNewManagerIfaceFunc *
storaged_module_get_new_manager_iface_funcs (void)
{
  StoragedModuleNewManagerIfaceFunc *funcs;

  funcs = g_new0 (StoragedModuleNewManagerIfaceFunc, 2);
  funcs[0] = &new_manager_initiator_iface;

  return funcs;
}
