#!/usr/bin/env -S node

// Script to install RedHttpClient in your game's directory.
// 
// Usage: node install.mjs [game-path]
import * as fs from 'fs';

const options = process.argv.slice(2);

const GAME_PATH = options.length > 0 ? options[0] : 'C:\\Program Files (x86)\\Steam\\steamapps\\common\\Cyberpunk 2077';
const RED4EXT_PATH = `${GAME_PATH}\\red4ext\\plugins`;
const REDSCRIPT_PATH = `${GAME_PATH}\\r6\\scripts`;

// Whether game directory exists?
if (!fs.existsSync(GAME_PATH)) {
    console.error(`[RedHttpClient] Could not find game directory at: ${GAME_PATH}`);
    process.exit(1);
}

// Whether RED4ext directory exists?
if (!fs.existsSync(RED4EXT_PATH)) {
    console.error(`[RedHttpClient] Could not find RED4ext directory at: ${RED4EXT_PATH}`);
    console.info('[RedHttpClient] Install RED4ext from https://docs.red4ext.com/getting-started/installing-red4ext');
    process.exit(2);
}

// Whether Redscript directory exists?
if (!fs.existsSync(REDSCRIPT_PATH)) {
    console.error(`[RedHttpClient] Could not find Redscript directory at: ${REDSCRIPT_PATH}`);
    console.info('[RedHttpClient] Install Redscript from https://wiki.redmodding.org/redscript/getting-started/downloads');
    process.exit(3);
}

const GAME_PLUGIN_PATH = `${RED4EXT_PATH}\\RedHttpClient`;
const GAME_SCRIPT_PATH = `${REDSCRIPT_PATH}\\RedHttpClient`;
const GAME_TEST_SCRIPT_PATH = `${REDSCRIPT_PATH}\\RedTest`;

// Optionally create plugin's directory.
if (!fs.existsSync(GAME_PLUGIN_PATH)) {
    fs.mkdirSync(GAME_PLUGIN_PATH);
    console.info(`[RedHttpClient] Plugin directory created at: ${GAME_PLUGIN_PATH}`);
}

// Delete all scripts, to prevent old (removed) scripts to persist.
fs.rmSync(GAME_SCRIPT_PATH, {force: true, recursive: true});
fs.mkdirSync(GAME_SCRIPT_PATH);
console.info(`[RedHttpClient] Script directory created at: ${GAME_SCRIPT_PATH}`);

fs.rmSync(GAME_TEST_SCRIPT_PATH, {force: true, recursive: true});
fs.mkdirSync(GAME_TEST_SCRIPT_PATH);
console.info(`[RedHttpClient] Test script directory created at: ${GAME_TEST_SCRIPT_PATH}`);


const BUILD_LIBRARY_PATH = `build\\Debug\\RedHttpClient.dll`;
const GAME_LIBRARY_PATH = `${GAME_PLUGIN_PATH}\\RedHttpClient.dll`;

fs.cpSync(BUILD_LIBRARY_PATH, GAME_LIBRARY_PATH, {force: true});
console.info(`[RedHttpClient] Library installed.`);

const BUILD_SCRIPT_PATH = `scripts\\RedHttpClient`;
const BUILD_TEST_SCRIPT_PATH = `scripts\\RedTest`;

fs.cpSync(BUILD_SCRIPT_PATH, GAME_SCRIPT_PATH, {force: true, recursive: true, preserveTimestamps: true});
fs.cpSync(BUILD_TEST_SCRIPT_PATH, GAME_TEST_SCRIPT_PATH, {force: true, recursive: true, preserveTimestamps: true});
console.info(`[RedHttpClient] Scripts installed.`);