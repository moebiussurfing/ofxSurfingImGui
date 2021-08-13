#include "ofNodeEditor.h"

ofNodeEditor::ofNodeEditor()
{

}

void ofNodeEditor::LinkAdded(ImGui::NodeEditor::NodePad*& src, ImGui::NodeEditor::NodePad*& sink)
{

    ofLogVerbose() << "New Connection: source=" << src->owner->name_ << ":" << " to " << sink->owner->name_;
}

void ofNodeEditor::LinkDeleted(ImGui::NodeEditor::NodePad*& src, ImGui::NodeEditor::NodePad*& sink)
{

    ofLogVerbose() << "Delete Connection: source=" << src->owner->name_ << " to " << sink->owner->name_;
}
