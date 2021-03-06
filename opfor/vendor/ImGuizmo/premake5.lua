project "ImGuizmo"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"ImCurveEdit.cpp",
		"ImCurveEdit.h",
		"ImGradient.cpp",
		"ImGradient.h",
		"ImGuizmo.cpp",
		"ImGuizmo.h",
		"ImSequencer.cpp",
		"ImSequencer.h",
		"example/imgui.h",
	}

	includedirs
	{
		"example"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"