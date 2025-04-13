
#pragma once


/*

	This class has useful constants:
	widgets sizes, default themes, fonts,
	...etc.
	To be used around many classes.

*/


//----

// DEBUG

#define SURFING_IMGUI__DEBUG_FONTS
//TODO: comment to bypass set default font on Begin

//----


// MODES, FEATURES, WORKFLOW, WIP STUFF OR DEBUG

// DEBUG PROFILER ENGINE
//#define SURFING_IMGUI__USE_PROFILE_DEBUGGER // comment to exclude some classes

// NOTIFIER ENGINE
#define SURFING_IMGUI__USE_NOTIFIER
#define SURFING_IMGUI__NOTIFIER_DEFAULT_DURATION 5000
//#define SURFING_IMGUI__NOTIFIER_SETTINGS_STANDALONE 
// if undefined settings will be bundled into main settings.

// GLOBAL SCALER ENGINE
#define SURFING_IMGUI__USE_GLOBAL_SCALE

// FONTS MODE
//#define SURFING_IMGUI__USE_CUSTOM_FONTS_PTR 
// TODO: DEBUG: Using pointer should improve a bit the memory usage..
// maybe is not important bc is a vector of pointers not the objects them selfs!

// MOUSE CONTROL MODE
//#define SURFING_IMGUI__USE_MOUSE_HANDLING_BY_IMGUI_INSTEAD_OF_GLFW 
// Mouse handled by ImGui Instead of the OF/GLFW. 
// Includes much mouse behaviors from imgui, as resize, waiting, text input etc
// Required disabled to allow overlay on windows capturer app.

// DOCKING HELPERS
#define SURFING__DOCKING_WORKFLOW_HANDLER_AUTODOCKING

//----

// SETTINGS MANAGEMENT

// Improved fixing exceptions when closing ofApp.
// We can disable automatic saving on exit and/or class destructor.
// Then we should save manually.
// Also implemented an approach to auto save when settings params change.

//#define SURFING_IMGUI__CREATE_EXIT_LISTENER 
// To enable that ofApp exit will call exit and save settings.

//#define SURFING_IMGUI__ENABLE_SAVE_ON_EXIT 
// To enable auto save on exit.

#define SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES 
// To enable auto save on every param change.

//#define SURFING_IMGUI__ENABLE_SAVE_ON_CHANGES_USING_LISTENER 
// Made by Roy for RF
// but currently disabled as code from @moebiussurfing worked too and has 'max one save per frame'

//----


// To fix weird resizing behaviors 
// when too big or too small resized windows

#define IMGUI_WIDTH_THRESHOLD_TO_CONSIDER_SMALL 300 
//#define IMGUI_WIDTH_THRESHOLD_TO_CONSIDER_SMALL 250 
// when a window width is less than that, 
// we can consider that the window is too small.
// we will use another layout pattern for some widgets.

// LEGACY
//#define PADDING_COMBO 0 // to fix some weird label forcing oversize window

//----

// Default Themes file-based

// Files must be in the default place:
// ofxSurfingImGui\Examples\09_ThemeEditor\bin\data\Gui\themes\
// Note that "/Gui/" is the default global path, but could be changed. (setName() or setPath())
// When files are not located there, then will load a hardcoded default theme: 
// ofxImGuiSurfing::ImGui_ThemeMoebiusSurfingV2();

// Night Theme (Default)
#define SURFING_IMGUI__THEME_NAME_NIGHT "moebiusSurfing.ini"

// Day Theme
#define SURFING_IMGUI__THEME_NAME_DAY "moebiusSurfingDay.ini"

//--

// Default settings files are:
// bin\data\Gui\SurfingGui_UI_Internal.json
// bin\data\Gui\SurfingGui_UI_Organizer.json

#define SURFING_IMGUI__DEFAULT_PATH_GLOBAL "Gui/"
#define SURFING_IMGUI__DEFAULT_NAME_LABEL "SurfingGui"

// But, to allow multiple instances, it can be customized, 
// before adding special windows and setup() by:
// 
// ui.setName("myOfApp");
// \bin\data\myOfApp\Gui\
// myOfApp_UI_Internal.json
// myOfApp_UI_Organizer.json

//----

// DEFAULT FONT

//TODO: could think about include fonts in themes or to create a JSON to allow customization.

// Notice that if not any font file is located, will work as ImGui default,
// So you don't need to put any files on bin/data to compile right!

#define OFX_IM_FONT_DEFAULT_PATH_FONTS "assets/fonts/" 
// main container for all the font files!

// Default font
#define OFX_IM_FONT_DEFAULT_SIZE_MIN 14
#define OFX_IM_FONT_DEFAULT_SIZE OFX_IM_FONT_DEFAULT_SIZE_MIN
#define OFX_IM_FONT_DEFAULT_FILE "Geist-Bold.ttf"

// Default mono-spaced font
#define OFX_IM_FONT_DEFAULT_MONO_SIZE_MIN 14
#define OFX_IM_FONT_DEFAULT_MONO_FILE "GeistMono-Bold.ttf"

// LEGACY font
#define OFX_IM_FONT_DEFAULT_FILE_LEGACY "JetBrainsMono-Bold.ttf"

//----

// RATIO SIZES BETWEEN SIZES OF A WIDGET TYPE. 

//TODO:
// fix for HSLIDERS.. 
// should be used by toggles and buttons too!
#define OFX_IM_WIDGETS_RATIO_BIG 1.50f
#define OFX_IM_WIDGETS_RATIO_DEFAULT 0.70f
#define OFX_IM_WIDGETS_RATIO_SMALL 0.40f
#define OFX_IM_WIDGETS_RATIO_MINI 0.16f

// Window scrolling size on some windows/groups
#define OFX_IM_HEIGHT_SCROLL_GROUP 400

//TODO: make it active 
// Knobs format to 3 decimals
#define OFX_IM_FORMAT_WIDGETS "%.1f"
#define OFX_IM_FORMAT_KNOBS "%.3f"
#define OFX_IM_FORMAT_SLIDERS "%.3f"

//TODO:
#define OFX_IM_FORMAT_WIDGETS_INT "%d"
#define OFX_IM_FORMAT_KNOBS_INT "%d"
#define OFX_IM_FORMAT_SLIDERS_INT "%d"

//----

#define OFX_IMGUI_CONSTRAIT_WINDOW_SHAPE 
// Constraint some window minimal shape sizes.

// Layout Presets Engine
#define SURFING_IMGUI__DEFAULT_AMOUNT_PRESETS 4 

//TODO:
// Testing central view-port
#define SURFING_IMGUI__FIXING_DRAW_VIEWPORT // To debug free space

//----

#define OFX_IM_TEXT_INACTIVE_ALPHA 0.30f // for using on toggle buttons

//#define OFX_IM_BLINK_MIN 0.2f 
//#define OFX_IM_BLINK_MAX 1.0f 
#define OFX_IM_BLINK_MIN 0.35f 
#define OFX_IM_BLINK_MAX 1.0f 

#define OFX_IM_FACTOR_DARKEN 0.2f 

//TODO: use another approach?
#define OFX_IM_VERTICAL_AMOUNT_UNITS 5.0f 

//----

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

//------

namespace ofxImGuiSurfing
{
	//--

	//--------------------------------------------------------------
	enum SurfingFontTypes
	{
		OFX_IM_FONT_DEFAULT = 0,
		OFX_IM_FONT_BIG,
		OFX_IM_FONT_HUGE,
		OFX_IM_FONT_HUGE_XXL,

		OFX_IM_FONT_DEFAULT_MONO,
		OFX_IM_FONT_BIG_MONO,
		OFX_IM_FONT_HUGE_MONO,
		OFX_IM_FONT_HUGE_XXL_MONO,

		OFX_IM_FONT_AMOUNT
	};

	//--

	// NOTE:
	// Now, these sizes are usually related to height! 
	// Because widgets widths are handled by the API args!
	// TODO: IDEA: Remake width management notation to use of percents.
	// TODO: IDEA: Add blink on hover styles

	//--------------------------------------------------------------
	enum SurfingGuiTypes
	{
		OFX_IM_DEFAULT = 0,
		// Default style for each widget. (kind of like ofxImGui does)

		OFX_IM_HIDDEN,
		// Omit widget. don't let spacing there.

		OFX_IM_DISABLED,
		// Make it invisible, preserve the void spacing. it's a common height but could differs..

		OFX_IM_INACTIVE,
		// Draws the widget. but makes it inactive. disables mouse control.

		OFX_IM_SPACING,
		// Make it invisible, preserve a custom (one standard line) spacing.

		//--

		// Types / Styles

		//--

		// Bool and void 

		// Button

		//OFX_IM_BUTTON_MINI,	// 1 = default. too small to place text well.
		OFX_IM_BUTTON_SMALL,	// 1 = default ratio
		OFX_IM_BUTTON,			// 1.25 ratio
		OFX_IM_BUTTON_MEDIUM,	// 1.5 ratio
		OFX_IM_BUTTON_BIG,		// 2 ratio
		OFX_IM_BUTTON_BIG_XXL,	// 3 ratio
		OFX_IM_BUTTON_BIG_XXXL, // 4 ratio

		//--

		// Border

		OFX_IM_BUTTON_SMALL_BORDER,
		OFX_IM_BUTTON_BORDER,
		OFX_IM_BUTTON_MEDIUM_BORDER,
		OFX_IM_BUTTON_BIG_BORDER,
		OFX_IM_BUTTON_BIG_XXL_BORDER,
		OFX_IM_BUTTON_BIG_XXXL_BORDER,

		//--

		// Border Blink 

		OFX_IM_BUTTON_SMALL_BORDER_BLINK,
		OFX_IM_BUTTON_BORDER_BLINK,
		OFX_IM_BUTTON_MEDIUM_BORDER_BLINK,
		OFX_IM_BUTTON_BIG_BORDER_BLINK,
		OFX_IM_BUTTON_BIG_XXL_BORDER_BLINK,
		OFX_IM_BUTTON_BIG_XXXL_BORDER_BLINK,

		//--

		// Bool (not void)

		// Toggle

		OFX_IM_CHECKBOX, // ofxImGui standard

		OFX_IM_TOGGLE,
		//OFX_IM_TOGGLE_MINI,
		OFX_IM_TOGGLE_SMALL,
		OFX_IM_TOGGLE_MEDIUM,
		OFX_IM_TOGGLE_BIG,
		OFX_IM_TOGGLE_BIG_XXL,
		OFX_IM_TOGGLE_BIG_XXXL,

		//--

		// Border

		OFX_IM_TOGGLE_SMALL_BORDER,
		OFX_IM_TOGGLE_BORDER,
		OFX_IM_TOGGLE_MEDIUM_BORDER,
		OFX_IM_TOGGLE_BIG_BORDER,
		OFX_IM_TOGGLE_BIG_XXL_BORDER,
		OFX_IM_TOGGLE_BIG_XXXL_BORDER,

		//--

		// Border Blink 

		OFX_IM_TOGGLE_SMALL_BORDER_BLINK,
		OFX_IM_TOGGLE_BORDER_BLINK,
		OFX_IM_TOGGLE_MEDIUM_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_XXL_BORDER_BLINK,
		OFX_IM_TOGGLE_BIG_XXXL_BORDER_BLINK,

		//--

		// Rounded

		OFX_IM_TOGGLE_ROUNDED,
		OFX_IM_TOGGLE_ROUNDED_MINI_XS,//TODO:
		OFX_IM_TOGGLE_ROUNDED_MINI,
		OFX_IM_TOGGLE_ROUNDED_SMALL,
		OFX_IM_TOGGLE_ROUNDED_MEDIUM,
		OFX_IM_TOGGLE_ROUNDED_BIG,

		//--

		// LEGACY. Now we removed 'button' word
		OFX_IM_TOGGLE_BUTTON_ROUNDED, // same size than small.
		OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI_XS,//TODO:
		OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_SMALL,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_MEDIUM,
		OFX_IM_TOGGLE_BUTTON_ROUNDED_BIG,

		//--

		// FLOAT / INT Styles

		OFX_IM_SLIDER, // uses the (ofxImGui) standard
		OFX_IM_SLIDER_NO_LABEL,//TODO:
		// Big Sliders

		// Horizontal

		OFX_IM_HSLIDER_BIG,
		OFX_IM_HSLIDER_BIG_NO_NAME,
		OFX_IM_HSLIDER_BIG_NO_NUMBER,
		OFX_IM_HSLIDER_BIG_NO_LABELS,
		OFX_IM_HSLIDER_SMALL,
		OFX_IM_HSLIDER_SMALL_NO_NAME,
		OFX_IM_HSLIDER_SMALL_NO_NUMBER,
		OFX_IM_HSLIDER_SMALL_NO_LABELS,
		OFX_IM_HSLIDER,
		OFX_IM_HSLIDER_NO_NAME,
		OFX_IM_HSLIDER_NO_NUMBER,
		OFX_IM_HSLIDER_NO_LABELS,
		OFX_IM_HSLIDER_MINI,
		OFX_IM_HSLIDER_MINI_NO_NAME,
		OFX_IM_HSLIDER_MINI_NO_LABELS,
		OFX_IM_HSLIDER_MINI_NO_NUMBER,

		//--

		// Vertical

		OFX_IM_VSLIDER,
		OFX_IM_VSLIDER_NO_NAME,
		OFX_IM_VSLIDER_NO_NUMBER,
		OFX_IM_VSLIDER_NO_LABELS,

		OFX_IM_PROGRESS_BAR_MINI,
		OFX_IM_PROGRESS_BAR_MINI_NO_TEXT,
		OFX_IM_PROGRESS_BAR,
		OFX_IM_PROGRESS_BAR_NO_TEXT,
		OFX_IM_STEPPER,
		OFX_IM_STEPPER_NO_LABEL,
		OFX_IM_STEPPER_RAW,
		OFX_IM_STEPPER_RAW_NO_LABEL,
		OFX_IM_DRAG,
		OFX_IM_DRAG_NO_LABEL,

		//--

		// Knobs

		// Notice that full width by default, is usually too big!
		// LEGACY
		OFX_IM_KNOB, // LEGACY
		OFX_IM_KNOB_TRAIL, // LEGACY. decorated

		//TODO:
		// Add more arguments: no label, no number...
		// Adding NEW style knobs, 
		// taken from Simon Altschuler 
		// https://github.com/altschuler/imgui-knobs

		OFX_IM_KNOB_TICKKNOB,
		OFX_IM_KNOB_DOTKNOB,
		OFX_IM_KNOB_WIPERKNOB,
		OFX_IM_KNOB_WIPERONLYKNOB,
		OFX_IM_KNOB_WIPERDOTKNOB,
		OFX_IM_KNOB_STEPPEDKNOB,
		OFX_IM_KNOB_SPACEKNOB,

		//--


		//TODO: 
		// multiple controls for fine tweak
		// for a single param
		OFX_IM_COMBO_MULTI,

		//--

		// Strings

		//TODO: add button and fix callback to trig 
		// when hitting enter or submit button clicked


		OFX_IM_TEXT_INPUT,
		OFX_IM_TEXT_INPUT_NO_NAME,
		OFX_IM_TEXT_INPUT_NAMED,
		OFX_IM_TEXT_INPUT_NAMED_PADDED, // to align with other clipped widgets like stepper

		//TODO: 
		// Get from bigTextInput widget
		// would be better to add it on v3 API 
		// with arguments as imgui does (bitwise shift).
		OFX_IM_TEXT_INPUT_HINT,

		OFX_IM_TEXT_DISPLAY,
		OFX_IM_TEXT_DISPLAY_WRAPPED,
		OFX_IM_TEXT_DISAPLAY_LONG,//to be used as long paragraph text blocks

		//OFX_IM_LABEL,//big font not accessible here..
		//OFX_IM_LABEL_BIG,

		//--

		// Colors

		OFX_IM_COLOR, // default
		OFX_IM_COLOR_INPUTS, // default
		OFX_IM_COLOR_INPUTS_NO_ALPHA, // without the alpha control
		OFX_IM_COLOR_NO_INPUTS, // without inputs
		OFX_IM_COLOR_NO_INPUTS_NO_ALPHA, // without inputs
		OFX_IM_COLOR_NO_NAME, //TODO: without name or controls
		OFX_IM_COLOR_BOX, // small box color without controls
		OFX_IM_COLOR_BOX_FULL_WIDTH, // full width
		OFX_IM_COLOR_BOX_FULL_WIDTH_BIG, // double height
		OFX_IM_COLOR_BOX_FULL_WIDTH_NO_ALPHA, // full width. no alpha
		OFX_IM_COLOR_BOX_FULL_WIDTH_BIG_NO_ALPHA, // double height. no alpha

		//--

		// Multi dimension 

		//TODO: 
		// for glm::vec2 vec3 vec4
		OFX_IM_MULTIDIM_SPLIT_SLIDERS,
		OFX_IM_MULTIDIM_SPLIT_SLIDERS_FOLDERED,
		//TODO: add more types
		//OFX_IM_MULTIDIM_SPLIT_STEPPERS,//TODO:
		//OFX_IM_MULTIDIM_SPLIT_DRAGS,

		//--

		OFX_IM_NUM_TYPES
	};

	//--

	// Group Style / State

	//TODO: 
	// NEW API V2
	// To simplify the API
	// We can use one only flag argument and multiple possibilities at the same time are allowed.
	typedef int SurfingGuiGroupStyle;
	enum SurfingGuiGroupStyle_
	{
		SurfingGuiGroupStyle_None = 1 << 0,
		SurfingGuiGroupStyle_Collapsed = 1 << 1,
		SurfingGuiGroupStyle_NoHeader = 1 << 2,
		SurfingGuiGroupStyle_Hidden = 1 << 3,
		SurfingGuiGroupStyle_HeaderSmall = 1 << 4 // uses ImGui tree without big header. just arrow.
		//SurfingGuiGroupStyle_NoArrow = 1 << 5,
	};

	//--

	// Group Style
	//TODO: kind of deprecated? replace by SurfingGuiGroupStyle_Collapsed?
	//it's used internally in some methods.. make it private?

	//--------------------------------------------------------------
	enum SurfingGuiTypesGroups
	{
		OFX_IM_GROUP_DEFAULT = 0,// TODO: BUG: it's forced collapsed
		OFX_IM_GROUP_COLLAPSED,
		OFX_IM_GROUP_TREE_EX, // TODO: can be collapsed or opened
		OFX_IM_GROUP_TREE, // TODO: BUG: it's forced collapsed
		OFX_IM_GROUP_SCROLLABLE,
		OFX_IM_GROUP_HIDDEN_HEADER, // hide header. TODO; fails on first group. not working
		OFX_IM_GROUP_HIDDEN, // hide header and all the content

		//OFX_IM_GROUP_WINDOWED, // creates a windows to populate into. Notice that must be a root group. can't be a nested! 
		//guiMnager is not in scope here!

		OFX_IM_GROUP_NUM_TYPES
	};

	//----

	//TODO: 
	// FEATURE:

	// Flags

	// Add a new flag to handle labels, 
	// active or tool tip NEW features
	typedef int SurfingGuiFlags;
	enum SurfingGuiFlags_
	{
		SurfingGuiFlags_None = 1 << 0,
		SurfingGuiFlags_NoTitle = 1 << 1,
		SurfingGuiFlags_NoInput = 1 << 2,
		SurfingGuiFlags_TooltipValue = 1 << 3,
		SurfingGuiFlags_TooltipHelp = 1 << 4,
		SurfingGuiFlags_DragHorizontal = 1 << 5,
		SurfingGuiFlags_Hidden = 1 << 6,
		SurfingGuiFlags_Disabled = 1 << 7,
		SurfingGuiFlags_Inactived = 1 << 8,
	};

	//----

	//TODO: should use another approach top avoid manually name each enum!
	// Helper to get the styles name for debugging purposes
	//--------------------------------------------------------------
	inline static std::string getSurfingGuiTypesGroupsName(int i)
	{
		std::string _groupInfo;
		if (i == 0) _groupInfo = "OFX_IM_GROUP_DEFAULT";
		else if (i == 1) _groupInfo = "OFX_IM_GROUP_COLLAPSED";
		else if (i == 2) _groupInfo = "OFX_IM_GROUP_TREE_EX";
		else if (i == 3) _groupInfo = "OFX_IM_GROUP_TREE";
		else if (i == 4) _groupInfo = "OFX_IM_GROUP_SCROLLABLE";
		else if (i == 5) _groupInfo = "OFX_IM_GROUP_HIDDEN_HEADER";
		else if (i == 6) _groupInfo = "OFX_IM_GROUP_HIDDEN";
		//else if (i == 7) _groupInfo = "OFX_IM_GROUP_WINDOWED";

		else _groupInfo = "OFX_IM_GROUP UNKNOWN";

		return _groupInfo;
	}

	//---------------

//----

//TODO:
// These arguments are to pass to setup(..) method 
// to simplify instantiation and define settings.
//--------------------------------------------------------------

// Argument to be used on ui.setup(mode);

	enum SurfingGuiMode
	{
		IM_GUI_MODE_UNKNOWN = 0,
		// Could be undefined when using LEGACY API maybe.

		IM_GUI_MODE_INSTANTIATED,
		// To include the ImGui context 
		// and requiring main begin/end.

		IM_GUI_MODE_INSTANTIATED_DOCKING,
		//TODO: should rename
		// Uses docking and the layout presets engine.
		// Allows docking between multiple instances too.

		IM_GUI_MODE_INSTANTIATED_DOCKING_RAW,
		// not using layout presets engine.
		// For advanced users accessing more internal ImGui stuff.
		// Requiring to call BeginDocking/EndDocking manually.

		IM_GUI_MODE_INSTANTIATED_DOCKING_RAW_AUTOHANDLER,
		// not using layout presets engine. 
		// Some auto-handled internal workflow.
		// will auto call BeginDocking/EndDocking internally.

		IM_GUI_MODE_INSTANTIATED_SINGLE,
		// To include the ImGui context and requiring begin/end 
		// but a single ImGui instance, no other add-ons.

		//IM_GUI_MODE_SPECIAL_WINDOWS, 
		//TODO: could simplify API, bc it's duplicated from 
		//ui.setWindowsMode(IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER);

		IM_GUI_MODE_REFERENCED,
		//TODO: -> To receive the parent (ofApp scope) 
		// ImGui object as reference.

		IM_GUI_MODE_NOT_INSTANTIATED
		// To render windows and widgets only. 
		// Inside an external ImGui context begin/end (newFrame).
	};

	//--

	// To enable Special windows mode.
	// Then handles Organizer and Align windows.
	enum SurfingGuiModeWindows
	{
		IM_GUI_MODE_WINDOWS_SPECIAL_UNKNOWN = 0,
		IM_GUI_MODE_WINDOWS_SPECIAL_DISABLED,
		IM_GUI_MODE_WINDOWS_SPECIAL_ORGANIZER
		//TODO: add other modes
	};

	//--

	//TODO:
	//// To help API memo..
	//// Can we do that and avoid to create the class functions on GuiManager?
	//#define ui.AddSpacingSmall() ofxImGuiSurfing::AddSpacingSmall() 
	//#define ui.AddSpacingDouble() ofxImGuiSurfing::AddSpacingDouble() 
	//#define ui.AddSpacing() ofxImGuiSurfing::AddSpacing() 
	//#define ui.AddSpacingBig() ofxImGuiSurfing::AddSpacingBig() 
	//#define ui.AddSpacingBigSeparated() ofxImGuiSurfing::AddSpacingBigSeparated() 
	//#define ui.AddSpacingSeparated() ofxImGuiSurfing::AddSpacingSeparated() 
	//#define ui.AddSpacingHuge() ofxImGuiSurfing::AddSpacingHuge() 
	//#define ui.AddSpacingHugeSeparated() ofxImGuiSurfing::AddSpacingHugeSeparated() 

};
