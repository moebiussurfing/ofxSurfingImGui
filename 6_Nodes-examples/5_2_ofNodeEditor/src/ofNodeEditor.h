#ifndef OFNODEEDITOR_H
#define OFNODEEDITOR_H

#include "ofMain.h"
#include "NodesEdit.h"

class ofNodeEditor : public ImGui::NodeEditor
{
public:
    ofNodeEditor();

    void LinkAdded(ImGui::NodeEditor::NodePad*& src, ImGui::NodeEditor::NodePad*& sink);
    void LinkDeleted(ImGui::NodeEditor::NodePad*& src, ImGui::NodeEditor::NodePad*& sink);
};

#endif // OFNODEEDITOR_H
