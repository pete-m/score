#pragma once
#include <iscore/command/SerializableCommand.hpp>
#include <iscore/tools/ModelPath.hpp>



#include <QString>

#include <tests/helpers/ForwardDeclaration.hpp>
class Process;
class LayerModel;
class RackModel;
class SlotModel;
class ConstraintModel;
namespace Scenario
{
    namespace Command
    {
        class AddLayerInNewSlot;
        class AddLayerModelToSlot;
        /**
        * @brief The AddProcessToConstraint class
        */
        class AddProcessToConstraint : public iscore::SerializableCommand
        {
                ISCORE_COMMAND_DECL_OBSOLETE("AddProcessToConstraint", "AddProcessToConstraint")
#include <tests/helpers/FriendDeclaration.hpp>
            public:
                ISCORE_SERIALIZABLE_COMMAND_DEFAULT_CTOR_OBSOLETE(AddProcessToConstraint, "ScenarioControl")
                AddProcessToConstraint(
                    Path<ConstraintModel>&& constraintPath,
                    QString process);

                virtual void undo() override;
                virtual void redo() override;

                const Path<ConstraintModel>& constraintPath() const
                { return m_path; }
                const Id<Process>& processId() const
                { return m_createdProcessId; }

            protected:
                virtual void serializeImpl(QDataStream&) const override;
                virtual void deserializeImpl(QDataStream&) override;

            private:
                Path<ConstraintModel> m_path;
                QString m_processName;

                Id<Process> m_createdProcessId {};
                Id<RackModel> m_createdRackId {};
                Id<SlotModel> m_createdSlotId {};
                Id<LayerModel> m_createdLayerId {};
                QByteArray m_layerConstructionData;
                bool m_noRackes = false;
                bool m_notBaseConstraint = false;
        };
    }
}



class AddOnlyProcessToConstraint : public iscore::SerializableCommand
{
        ISCORE_COMMAND_DECL("ScenarioControl", "AddOnlyProcessToConstraint", "AddOnlyProcessToConstraint")
    public:
        ISCORE_SERIALIZABLE_COMMAND_DEFAULT_CTOR(AddOnlyProcessToConstraint)
        AddOnlyProcessToConstraint(
            Path<ConstraintModel>&& constraintPath,
            QString process);

        void undo() override;
        void redo() override;

        const Id<Process>& processId() const
        { return m_createdProcessId; }

    protected:
        void serializeImpl(QDataStream& s) const override;
        void deserializeImpl(QDataStream& s) override;

    private:
        Path<ConstraintModel> m_path;
        QString m_processName;

        Id<Process> m_createdProcessId {};
};
