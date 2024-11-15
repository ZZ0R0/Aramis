from mythic_container.MythicCommandBase import *
from mythic_container.MythicRPC import *


class LsArguments(TaskArguments):

    def __init__(self, command_line, **kwargs):
        super().__init__(command_line, **kwargs)
        self.args = [
            CommandParameter(
                name="path",
                cli_name="path",
                display_name="Path to list files from.",
                type=ParameterType.String,
                description="Path to list files from.",
                parameter_group_info=[
                    ParameterGroupInfo(
                        required=False, group_name="Default", ui_position=1
                    ),
                ],
            ),
        ]

    async def parse_arguments(self):
        # Check if named parameters were defined
        cli_names = [arg.cli_name for arg in self.args if arg.cli_name is not None]
        if (
            any([self.raw_command_line.startswith(f"-{cli_name} ") for cli_name in cli_names])
            or any([f" -{cli_name} " in self.raw_command_line for cli_name in cli_names])
        ):
            args = json.loads(self.command_line)
        # Freeform unmatched arguments
        else:
            args = {"path": "."}
            if len(self.raw_command_line) > 0:
                args["path"] = self.raw_command_

class LsCommand(CommandBase):
    cmd = "ls"
    needs_admin = False
    help_cmd = "ls [path]"
    description = "List files and folders in a specified directory (defaults to your current working directory.)"
    version = 3
    supported_ui_features = ["file_browser:list"]
    author = "@ZZ0R0"
    argument_class = LsArguments
    attackmapping = ["T1106", "T1083"]
    attributes = CommandAttributes(
        supported_os=[SupportedOS.Windows ]
    )

    async def create_tasking(self, task: MythicTask) -> MythicTask:
        task.display_params = task.args.get_arg("path")
        return task

    async def process_response(self, task: PTTaskMessageAllData, response: any) -> PTTaskProcessResponseMessageResponse:
        resp = PTTaskProcessResponseMessageResponse(TaskID=task.Task.ID, Success=True)
        return resp