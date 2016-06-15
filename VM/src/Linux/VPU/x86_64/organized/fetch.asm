/*
	*=========================================================================*
	|     The Ditto Virtual Machine | Written by Bobby Crawford (ozdevguy)    |
	|				    http://www.crawford-online.com						  |	
	|																		  |
	|	This program is free software: you can redistribute it and/or modify  |
	|    it under the terms of the GNU General Public License as published by |
	|    the Free Software Foundation, either version 3 of the License, or    |
	|    (at your option) any later version.								  | 	
	|																		  | 	
	|   This program is distributed in the hope that it will be useful,       |
	|    but WITHOUT ANY WARRANTY; without even the implied warranty of       |
	|    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        |
	|    GNU General Public License for more details.                         |
	|																	      |
	|    You should have received a copy of the GNU General Public License    |
	|    along with this program.  If not, see <http://www.gnu.org/licenses/>.| 
	|																		  |
	|																		  |
	*=========================================================================*

	Intel 64 Architecture
	======================

	-> INITIATE INSTRUCTION FETCH (fetch.asm)
	This file contains the assembly instructions required to initiate an instruction fetch.

	Before performing any work relating to the actual instruction fetch, we need to see if a virtual
	interrupt has been rasied. If an interrupt has been raised, we perform the necessary actions by
	jumping to the virtual hardware interrupt handler. If an interrupt has not been raised, we can
	successfully begin fetching the next instruction based on the memory address in the instruction pointer. 
	In order to fetch the instruction correctly, we need to call the appropriate MMU instruction fetch function
	for the current VPU operating mode (privileged vs. protected).

*/


ivpu_fetch:

	#Hardware interrupt check.
	mov rbx, 0x400										#Create a mask for the HI flag in the FLAGS register (RSI).
	mov rcx, 0x0										#Move 0 into rcx.
	and rbx, rsi										#Get the HI flag by applying the mask to the FLAGS register (RSI).
	cmovnz rcx, qword ptr [r14 + 2208]					#Move the HWI register from the  VPU vector into rcx (if HI is enabled).
	test rbx, rcx										#Check to see if both the HI flag and Hardware Interrupt Detected bits are set.
	mov rax, offset ivpu_fetch_cont                  	#Move the address of ivpu_fetch_cont into rax
	mov rdx, offset ivpu_hardware_interrupt_handler     #Move the address of _hardware_interrupt_handler into rdx
	cmovz rdx, rax										#If the HI flag and Hardware Interrupt Detected bits are not BOTH active, place the _contFetch address into rdx.
	jmp rdx												#Jump to the address in rdx.

ivpu_fetch_cont: 										#Continue the instruction fetch process...
	test rsi, 0x2000									#Check the PR flag in the FLAGS register.
	jnz ivpu_mmu_fetch_instruction_prot                 #If the PR flag is set, fetch the instruction from the MMU in protected mode.
	jmp ivpu_mmu_fetch_instruction_priv					#If the PR flag is not set, fetch the instruction from the MMU in privileged mode.

