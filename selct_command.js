const [, , ...command_from_stdin] = process.argv;
const command = command_from_stdin.join(' ');

const alias = {
  l: 'ls -l',
};

const variables = {
  pathr: '/user',
};

const process_alias = function (command) {
  const parts = command.split(' ');
  const deAliased = parts.map((part) => {
    if (alias[part]) return alias[part];
    return part;
  });
  if (deAliased[0] == 'alias') {
    if (deAliased[1]) {
      if (deAliased[1].includes('=')) {
        const [key, value] = deAliased[1].split('=');
        if (value == '') throw new Error('incorrect alias');
        const [, , ...otherAttributes] = deAliased;
        alias[key] = [value, ...otherAttributes].join(' ');
        return deAliased.join(' ');
      } else console.log(alias[parts[1]]);
    } else {
      Object.keys(alias).forEach((a) => console.log(alias[a]));
    }
  }
  return deAliased.join(' ');
};

const processVariable = function (command) {
  const parts = command.split(' ');
  return parts
    .map((part) => {
      if (variables[part]) return variables[part];
      return part;
    })
    .join(' ');
};

const processCommand = function (command) {
  let finalCommand = processVariable(command);
  finalCommand = process_alias(finalCommand);
  return finalCommand;
};

console.log(processCommand(command));
