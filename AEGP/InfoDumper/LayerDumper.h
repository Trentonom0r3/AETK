#include <AETK/AEGP/AEGP.hpp>
#include "windows.h"
#include <fstream> // Include this for file operations
#include <sstream> // For std::ostringstream


static A_long				S_idle_count = 0L;

class LayerDumperCommand : public Command {
	public:
		LayerDumperCommand() : Command("LayerDumper", MenuID::LAYER) {}

	void execute() override;

	void updateMenu() override;

private:
	std::ostringstream logOss; // Used to accumulate log messages
    std::string filePath = ""; // File path for the log file    

    inline std::string StreamTypeToString(StreamType streamType) { // Helper function to convert StreamType to string
        switch (streamType) {
        case StreamType::NONE: return "NONE";
        case StreamType::ThreeD_SPATIAL: return "3D SPATIAL";
        case StreamType::ThreeD: return "3D";
        case StreamType::TwoD_SPATIAL: return "2D SPATIAL";
        case StreamType::TwoD: return "2D";
        case StreamType::OneD: return "1D";
        case StreamType::COLOR: return "COLOR";
        case StreamType::ARB: return "ARB";
        case StreamType::MARKER: return "MARKER";
        case StreamType::LAYER_ID: return "LAYER_ID";
        case StreamType::MASK_ID: return "MASK_ID";
        case StreamType::MASK: return "MASK";
        case StreamType::TEXT_DOCUMENT: return "TEXT_DOCUMENT";
        default: return "Unknown StreamType";
        }
    }

    inline void openWindow() {
        void* hwnd = App::GetWindow();
        if (hwnd) {
            //open window to select file
            OPENFILENAME ofn;
            char szFile[260];
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = (HWND)hwnd;
            ofn.lpstrFile = szFile;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szFile);
            ofn.lpstrFilter = "Text Files\0*.txt\0All Files\0*.*\0";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
            if (GetOpenFileName(&ofn) == TRUE) {
				filePath = ofn.lpstrFile;
			}
        }
    }

    inline void clearLogFile() {
        std::ofstream clearFile(filePath, std::ofstream::out | std::ofstream::trunc);
        clearFile.close();
    }

    // Dedicated function for logging exceptions
    inline void logException(const std::exception& e, const std::string& context) {
        logOss << "Exception: " << e.what() << " in " << context << "\n";
    }

    // Helper to generate indentation based on hierarchy depth
    std::string indent(int level) {
        return std::string(level * 4, ' '); // Adjust space count as needed
    }

    // Logging property details with improved structure
    inline void logPropertyDetails(const std::shared_ptr<BaseProperty>& prop, std::ofstream& outFile, int indentLevel) {
        auto propName = prop->getName();
        auto matchName = prop->matchName();
        auto propType = StreamTypeToString(prop->getType());
        auto numKeys = prop->numKeys();

        outFile << indent(indentLevel) << "Property:\n"
            << indent(indentLevel + 1) << "Name: " << propName << "\n"
            << indent(indentLevel + 1) << "Match Name: " << matchName << "\n"
            << indent(indentLevel + 1) << "Type: " << propType << "\n"
            << indent(indentLevel + 1) << "# of KeyFrames: " << numKeys << "\n";
    }

    // Enhanced property processing with clearer group delineation
    inline void processProperty(const std::shared_ptr<BaseProperty>& prop, std::ofstream& outFile, int indentLevel) {
        try {
            // Property details logging
            logPropertyDetails(prop, outFile, indentLevel);

            if (prop->getType() == StreamType::NONE && DynamicStreamSuite().GetStreamGroupingType(prop->getStream()) != StreamGroupingType::LEAF) {
                // Clearer delineation for groups with sub-properties
                outFile << indent(indentLevel) << "Contains Sub-properties:\n";
                auto group = std::static_pointer_cast<PropertyGroup>(prop);
                for (int i = 0; i < group->getNumProperties(); ++i) {
                    processProperty(group->getPropertyByIndex(i), outFile, indentLevel + 1);
                }
            }
            outFile << "\n"; // Adds spacing after each property or group for better readability
        }
        catch (const std::exception& e) {
            logException(e, "property operations");
            outFile << logOss.str(); // Ensure consistent structure in case of exceptions
        }
    }
    // Function to check if a specific flag is set
    bool IsFlagSet(DynStreamFlag flags, DynStreamFlag flagToCheck) {
        return static_cast<int>(flags) & static_cast<int>(flagToCheck);
    }

    // Simplifying the layer processing for better readability
    inline void processLayer(const std::shared_ptr<Layer>& layer, std::ofstream& outFile, int indentLevel = 0) {
        try {
            outFile << indent(indentLevel) << "Layer Details:\n"
                << indent(indentLevel + 1) << "Name: " << layer->getName() << "\n"
                << indent(indentLevel + 1) << "Match Name: " << layer->matchName() << "\n"
                << indent(indentLevel + 1) << "Layer Duration: " << layer->duration() << "\n"
                << indent(indentLevel + 1) << "Layer InPoint: " << layer->inPoint() << "\n"
                << indent(indentLevel + 1) << "Properties Count: " << layer->getNumProperties() << "\n";
            for (int i = 0; i < layer->getNumProperties(); ++i) {
                auto prop = layer->getPropertyByIndex(i);
                auto flags = DynamicStreamSuite().GetDynamicStreamFlags(prop->getStream());
                if (IsFlagSet(flags, DynStreamFlag::HIDDEN) || IsFlagSet(flags, DynStreamFlag::DISABLED) || IsFlagSet(flags, DynStreamFlag::ELIDED))
                {
					continue; // Skip hidden or disabled properties
				}
                else {
					processProperty(prop, outFile, indentLevel + 1);
				}
            }
            outFile << "\n"; // Adds a space after each layer for separation
        }
        catch (const std::exception& e) {
            logException(e, "layer operations");
            outFile << logOss.str();
        }
    }


    inline void process(std::shared_ptr<Layer> layer) {
        std::ofstream outFile(filePath, std::ios_base::app);
        outFile << "Processing Layer\n";
        try {
            processLayer(layer, outFile);
        }
        catch (const std::exception& e) {
            logException(e, "layer retrieval");
            outFile << logOss.str();
        }
        outFile.close();
    }

};

class LayerDumper : public Plugin {
	public:
		LayerDumper(struct SPBasicSuite* pica_basicP,
		AEGP_PluginID aegp_plugin_id,
		AEGP_GlobalRefcon* global_refconV)
		: Plugin(pica_basicP, aegp_plugin_id, global_refconV)
	{
	}

	inline void onInit();

    void onDeath();

	void onIdle();
};