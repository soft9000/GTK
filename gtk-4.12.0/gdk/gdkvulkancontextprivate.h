/* GDK - The GIMP Drawing Kit
 *
 * gdkvulkancontextprivate.h: specific Vulkan wrappers
 *
 * Copyright © 2016  Benjamin Otte
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "gdkvulkancontext.h"

#include "gdkdebugprivate.h"
#include "gdkdrawcontextprivate.h"
#include "gdkenums.h"

#ifdef GDK_RENDERING_VULKAN
#include <vulkan/vulkan.h>
#endif

G_BEGIN_DECLS

#define GDK_VULKAN_CONTEXT_CLASS(klass) 	(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_VULKAN_CONTEXT, GdkVulkanContextClass))
#define GDK_IS_VULKAN_CONTEXT_CLASS(klass)	(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_VULKAN_CONTEXT))
#define GDK_VULKAN_CONTEXT_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_VULKAN_CONTEXT, GdkVulkanContextClass))

typedef struct _GdkVulkanContextClass GdkVulkanContextClass;

struct _GdkVulkanContext
{
  GdkDrawContext parent_instance;
};

struct _GdkVulkanContextClass
{
  GdkDrawContextClass parent_class;

#ifdef GDK_RENDERING_VULKAN
  VkResult     (* create_surface)       (GdkVulkanContext       *context,
                                         VkSurfaceKHR           *surface);
#endif
};

#ifdef GDK_RENDERING_VULKAN

static inline VkResult
gdk_vulkan_handle_result (VkResult    res,
                          const char *called_function)
{
  if (res != VK_SUCCESS)
    {
      GDK_DEBUG (VULKAN, "%s(): %s (%d)", called_function, gdk_vulkan_strerror (res), res);
    }

  return res;
}

#define GDK_VK_CHECK(func, ...) gdk_vulkan_handle_result (func (__VA_ARGS__), G_STRINGIFY (func))

gboolean                gdk_display_ref_vulkan                          (GdkDisplay            *display,
                                                                         GError               **error);
void                    gdk_display_unref_vulkan                        (GdkDisplay            *display);

VkShaderModule          gdk_display_get_vk_shader_module                (GdkDisplay            *display,
                                                                         const char            *resource_name);

VkPipelineCache         gdk_vulkan_context_get_pipeline_cache           (GdkVulkanContext      *self);
void                    gdk_vulkan_context_pipeline_cache_updated       (GdkVulkanContext      *self);

GdkMemoryFormat         gdk_vulkan_context_get_offscreen_format         (GdkVulkanContext      *context,
                                                                         GdkMemoryDepth         depth);

#else /* !GDK_RENDERING_VULKAN */


static inline gboolean
gdk_display_ref_vulkan (GdkDisplay  *display,
                        GError     **error)
{
  GDK_DISPLAY_DEBUG (display, VULKAN, "Support for Vulkan disabled at compile-time");
  g_set_error_literal (error, GDK_VULKAN_ERROR, GDK_VULKAN_ERROR_UNSUPPORTED,
                       "Vulkan support was not enabled at compile time.");

  return FALSE;
}

#endif /* !GDK_RENDERING_VULKAN */

G_END_DECLS

