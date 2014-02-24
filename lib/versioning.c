/*
 * Copyright (c) 2002-2011 BalaBit IT Ltd, Budapest, Hungary
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */
#include <glib.h>
#include "versioning.h"


static gboolean
is_ose_version(gint version)
{
  return (version < 0x0400);
}

/*
  return the converted version value (OSE <-> PE versions)
*/
static gint
convert_ose_version_to_pe(gint version)
{
  gint ver_main = (version >> 8) & 0xFF;
  gint ver_sub = version & 0xFF;

  if (ver_main == 3 && ver_sub == 3)
    {
      ver_main = 4;
      ver_sub = 1;
    }
  else if (ver_main == 3 && (ver_sub == 1 || ver_sub == 2))
    {
      ver_main = 4;
      ver_sub = 0;
    }

  return (ver_main << 8) | ver_sub;
}

gint
compare_versions(gint version1, gint version2)
{
  gint converted_version1 = is_ose_version(version1) ? convert_ose_version_to_pe(version1) : version1;
  gint converted_version2 = is_ose_version(version2) ? convert_ose_version_to_pe(version2) : version2;

  if (converted_version1 < converted_version2)
    return -1;
  if (converted_version1 > converted_version2)
    return 1;
  return 0;
}

gboolean
check_config_version(gint version, gint required_version)
{
  return (compare_versions(version, required_version) >= 0);
}