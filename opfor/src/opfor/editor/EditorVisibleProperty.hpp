#pragma once

#include <Refureku/Refureku.h>
#include <Refureku/TypeInfo/Properties/PropertySettings.h>
#include <generated/EditorVisibleProperty.rfk.h>

namespace opfor OP4NAMESPACE()
{

struct OP4STRUCT(PropertySettings(rfk::EEntityKind::Field)) EditorVisible : rfk::Property
{
    opfor::Optional<opfor::String> editorName = std::nullopt;

    EditorVisible() noexcept = default;

    EditorVisible(opfor::String name) noexcept : editorName(name)
    {
    }

    EditorVisible_GENERATED
};

} // namespace opfor

File_GENERATED
